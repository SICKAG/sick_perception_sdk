import argparse
from packaging import version
from prance import ResolvingParser
from tabulate import tabulate
from typing import Any, Dict, List, Optional, Tuple
import os
import glob
import yaml

from objects import DeviceMetadata, EndpointDescription
from parser import parse_path
from generator import generate_code, generate_aggregate_headers
from table_generator import generate_configuration_table


def detect_device_metadata_from_path(filepath: str, schema_root: str) -> DeviceMetadata:
    """
    Detect device family, device_type, and determine version placeholder from the file path.

    Directory structure rules:
    - If YAML is directly in family folder: no variant (e.g., schema/LRS4000/LRS4000_V1.9.0.yaml)
    - If YAML is in a subfolder: that subfolder is the variant (e.g., schema/picoScan100/picoScan120/...)

    Args:
        filepath: Path to the OpenAPI specification file
        schema_root: Path to the schema directory (families are immediate subdirectories)

    Returns:
        DeviceMetadata with family, device_type, and placeholder version

    Raises:
        Exception: If the path structure doesn't match expected patterns
    """
    abs_path = os.path.abspath(filepath)
    abs_schema_root = os.path.abspath(schema_root)

    # Get the relative path from schema root
    if not abs_path.startswith(abs_schema_root):
        raise Exception(f"File '{filepath}' is not within schema root '{schema_root}'")

    rel_path = os.path.relpath(abs_path, abs_schema_root)
    parts = rel_path.split(os.sep)

    if len(parts) == 2:
        # No variant: family/file.yaml
        family = parts[0]
        device_type = family  # Same as family when no variant
    elif len(parts) == 3:
        # Has variant: family/variant/file.yaml
        family = parts[0]
        device_type = parts[1]  # Variant name
    else:
        raise Exception(f"Unexpected path structure: {filepath}. Expected family/file.yaml or family/variant/file.yaml")

    # Version will be extracted from YAML later; use placeholder for now
    return DeviceMetadata(family=family, device_type=device_type, version="unknown")


def find_yaml_files(schema_dir: str) -> List[str]:
    """
    Find all YAML files in the schema directory.

    Args:
        schema_dir: Path to the schema directory

    Returns:
        List of file paths to YAML files
    """
    yml_files = glob.glob(os.path.join(schema_dir, "**", "*.yml"), recursive=True)
    yaml_files = glob.glob(os.path.join(schema_dir, "**", "*.yaml"), recursive=True)
    all_files = sorted(yml_files + yaml_files)

    if not all_files:
        print(f"⚠️  Warning: No .yml or .yaml files found in directory '{schema_dir}'")
        return []

    print(f"ℹ️  Found {len(all_files)} YAML file(s) in directory '{schema_dir}'")
    return all_files


def get_blocked_paths(config_path) -> List[str]:
    """
    Try to read the list of blocked paths from the specified configuration file.
    If the file does not exist or cannot be parsed, an empty list is returned.
    """
    try:
        with open(config_path, "r") as f:
            config = yaml.safe_load(f)
        if not isinstance(config, dict):
            return []
        blocked_paths = config.get("blocked_paths")
        if isinstance(blocked_paths, list):
            return blocked_paths
        return []
    except Exception as e:
        print(f"❌  Cannot load configuration from '{config_path}': {e}")
        return []


def parse_openapi_file(filename: str, metadata: DeviceMetadata, config_path: Optional[str] = None) -> Tuple[List[EndpointDescription], DeviceMetadata]:
    """
    Parse a single OpenAPI specification file and return endpoint descriptions and updated metadata.

    Args:
        filename: Path to the OpenAPI specification file
        metadata: Device metadata (family, device_type - version will be updated from YAML)
        config_path: Optional path to configuration file with blocked paths

    Returns:
        Tuple of (endpoint_descriptions, updated_metadata with version from YAML)
    """
    # Get the list of blocked paths from the configuration file (if specified).
    blocked_paths = get_blocked_paths(config_path) if config_path else []

    # Parse the specified OpenAPI document. This gives us a deeply nested dictionary.
    device_desc = f"{metadata.family}/{metadata.device_type}" if metadata.device_type != metadata.family else metadata.family
    print(f"ℹ️  Parsing OpenAPI specification from '{filename}' for device '{device_desc}'.")
    parser = ResolvingParser(filename)
    spec: Dict[str, Any] = parser.specification  # type: ignore
    device_version = spec["info"]["version"]

    # Update metadata with actual version from YAML
    metadata = DeviceMetadata(family=metadata.family, device_type=metadata.device_type, version=device_version)
    print(f"ℹ️  Device '{metadata.device_type}' version '{device_version}'.")

    min_version = "1.1.0"
    if "x-sick-openapi-generator-version" in spec["info"]:
        sick_openapi_generator_version = spec["info"]["x-sick-openapi-generator-version"]
        if version.parse(sick_openapi_generator_version) < version.parse(min_version):
            print(
                f"⚠️  OpenAPI specification '{filename}' specifies 'info/x-sick-openapi-generator-version' as '{sick_openapi_generator_version}', which is below the minimum supported version of {min_version}. Skipping this file."
            )
            return [], metadata
    else:
        print(
            f"⚠️  OpenAPI specification '{filename}' does not specify 'info/x-sick-openapi-generator-version'. The minimum supported version is {min_version}. If any errors occur, you are on your own."
        )

    # Parse the paths and collect their data objects.
    print(f"ℹ️  Parsing paths...")
    endpoint_descriptions: List[EndpointDescription] = []
    for path_name, path in spec["paths"].items():
        if path_name in blocked_paths:
            print(f"⚠️  Ignoring path '{path_name}' because it is in the blocked_paths list.")
            continue

        try:
            parse_path(path_name, path, endpoint_descriptions)
        except Exception as e:
            print(f"❌  Error parsing path '{path_name}': {e}")
            continue
    print(f"ℹ️  Found {len(endpoint_descriptions)} valid endpoint descriptions.")

    return endpoint_descriptions, metadata


if __name__ == "__main__":
    # Fetch a few command line arguments
    parser = argparse.ArgumentParser(description="SICK Sensor SDK Open API Parser. Parses a SICK OpenAPI specification and generates C++ data objects.")
    parser.add_argument(
        "schema_dir",
        help="Path to the schema directory containing device family subdirectories with YAML files.",
    )
    parser.add_argument("-c", "--config", help="Path to the configuration file (YAML)")
    parser.add_argument("--dry-run", action="store_true", help="If set, only the OpenAPI document will be parsed; no C++ files will be written.")
    args = parser.parse_args()

    # Find all YAML files in schema directory
    filenames = find_yaml_files(args.schema_dir)

    # Auto-detect device metadata from directory structure
    print(f"ℹ️  Auto-detecting device metadata from directory structure...")
    metadata_list: List[DeviceMetadata] = []
    for filename in filenames:
        metadata = detect_device_metadata_from_path(filename, args.schema_dir)
        metadata_list.append(metadata)
        desc = f"{metadata.family}/{metadata.device_type}" if metadata.device_type != metadata.family else metadata.family
        print(f"ℹ️  Detected '{desc}' from '{filename}'")

    # Parse all OpenAPI files
    print(f"\n\nℹ️  Parsing {len(filenames)} OpenAPI specification file(s)...")
    all_endpoints: List[Tuple[List[EndpointDescription], DeviceMetadata]] = []
    for filename, metadata in zip(filenames, metadata_list):
        endpoint_descriptions, updated_metadata = parse_openapi_file(filename, metadata, args.config)
        if len(endpoint_descriptions) == 0:
            print(f"⚠️  No valid endpoint descriptions found for '{filename}'. Skipping code generation for this file.")
            continue

        # Print a summary for this device
        desc = f"{updated_metadata.device_type} v{updated_metadata.version}"
        print(f"\nℹ️  Summary for {desc}:")
        headers = ["path", "has GET response", "has POST request", "has POST response", "is SOPAS method"]
        lines = []
        for endpoint in endpoint_descriptions:
            has_get_response = "🟢" if endpoint.get is not None and endpoint.get.response_payload is not None else "⚪"
            has_post_request = "🟢" if endpoint.post is not None and endpoint.post.request_payload is not None else "⚪"
            has_post_response = "🟢" if endpoint.post is not None and endpoint.post.response_payload is not None else "⚪"
            is_sopas_method = "🟠" if endpoint.is_sopas_method else "⚪"
            line = [endpoint.path, has_get_response, has_post_request, has_post_response, is_sopas_method]
            lines.append(line)
        print(tabulate(lines, headers, colalign=("left", "center", "center", "center", "center")))

        # Store for code generation
        all_endpoints.append((endpoint_descriptions, updated_metadata))

    # Now that the payloads have been collected we can proceed to generating the C++ code and table.
    if not args.dry_run:
        # Generate C++ code for each device/version
        for endpoint_descriptions, metadata in all_endpoints:
            generate_code(endpoint_descriptions, metadata)

        # Generate aggregate headers (variant/family headers with latest alias)
        generate_aggregate_headers(all_endpoints)

        # Generate configuration overview table
        device_data = {
            metadata: endpoint_descriptions
            for endpoint_descriptions, metadata in all_endpoints
        }
        generate_configuration_table(device_data)
    else:
        print(f"\nℹ️  Skipping output generation because dry run was specified.")

    print(f"\n✅  All done. Have a nice day 😊")
