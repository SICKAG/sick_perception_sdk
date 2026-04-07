from io import TextIOWrapper
import os
from typing import List, Optional, Set, Dict, Tuple
from datetime import datetime
from collections import defaultdict

from packaging.version import Version

from objects import DeviceMetadata, EndpointDescription, EndpointMethodDescription, ObjectDescription, FieldDescription, EnumDescription


DATA_OBJECT_OUT_DIR = os.path.join("src/sensor_configuration/include/sick_perception_sdk/sensor_configuration/api")
MEMBER_PREFIX = "_"


def _get_namespace_name(metadata: DeviceMetadata) -> str:
    """Returns the name to use in C++ namespace (device_type, which is variant if exists, else family)."""
    return metadata.device_type


def _get_version_namespace(metadata: DeviceMetadata) -> str:
    """Returns the version in namespace format: v2_2_1."""
    return "v" + metadata.version.replace(".", "_")


def _is_variant(metadata: DeviceMetadata) -> bool:
    """Returns True if the device has a variant (device_type differs from family)."""
    return metadata.device_type != metadata.family


def _get_output_dir(metadata: DeviceMetadata) -> str:
    """
    Get the output directory for endpoint headers based on metadata.

    For families WITH variants: api/{family}/{variant}/{version}/
    For families WITHOUT variants: api/{family}/{version}/
    """
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        return os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, metadata.device_type, version_dir))
    else:
        return os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, version_dir))


def _get_include_prefix(metadata: DeviceMetadata) -> str:
    """
    Get the include path prefix for generated headers.

    For families WITH variants: sick_perception_sdk/sensor_configuration/api/{family}/{variant}/{version}
    For families WITHOUT variants: sick_perception_sdk/sensor_configuration/api/{family}/{version}
    """
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        return f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{metadata.device_type}/{version_dir}"
    else:
        return f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{version_dir}"


def generate_code(endpoints: List[EndpointDescription], metadata: DeviceMetadata):
    """Generate C++ code for all endpoints of a specific device/version."""
    out_dir = _get_output_dir(metadata)
    print(f"ℹ️  Generating output in '{out_dir}'...")

    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    for endpoint in endpoints:
        file_name = f"{endpoint.class_name}.g.hpp"
        full_file_name = os.path.join(out_dir, file_name)

        f = open(full_file_name, "w")
        _generate_file_header(f, file_name, metadata, endpoint)

        includes = set()
        for method in endpoint.get, endpoint.post:
            if method is not None:
                if method.request_payload is not None:
                    _collect_includes(method.request_payload, includes)
                if method.response_payload is not None:
                    _collect_includes(method.response_payload, includes)
        includes = sorted(includes)
        _generate_includes(f, includes)

        _generate_namespaces_start(f, metadata)

        name_of_name_member = "variableName" if not endpoint.is_sopas_method else "methodName"

        f.write(f"/**\n")
        f.write(f" * @brief Payloads for endpoint {endpoint.path}.\n")
        f.write(f"*/\n")
        f.write(f"struct {endpoint.class_name}\n{{\n\n")
        f.write(f'  constexpr static const char* {name_of_name_member} = "{endpoint.class_name}";\n')
        f.write(f"  constexpr static const bool isSopasMethod = {str(endpoint.is_sopas_method).lower()};\n\n")
        _generate_objects_for_endpoint_method(f, endpoint.get)
        _generate_objects_for_endpoint_method(f, endpoint.post)
        f.write(f"}}; // struct {endpoint.class_name}\n\n")
        _generate_namespaces_end(f, metadata)

        f.close()

    _generate_json(endpoints, metadata)

    _generate_version_include(endpoints, metadata)


def _generate_objects_for_endpoint_method(f: TextIOWrapper, method: Optional[EndpointMethodDescription]):
    if method is None:
        return

    if method.description is not None:
        f.write(f"  /**\n")
        f.write(f"   * @brief {method.description}\n")
        f.write(f"   */\n")

    f.write(f"  struct {method.method}\n  {{\n")

    _generate_object_for_payload(f, method.request_payload)
    _generate_object_for_payload(f, method.response_payload)

    f.write(f"  }}; // struct {method.method}\n\n")


def _generate_object_for_payload(f: TextIOWrapper, payload: Optional[ObjectDescription]):
    if payload is None:
        return

    _generate_object(f, payload, 4)
    f.write("\n")


def _get_json_include_prefix(metadata: DeviceMetadata) -> str:
    """
    Get the include path prefix for generated JSON headers.

    For families WITH variants: sick_perception_sdk/sensor_configuration/api/{family}/{variant}/{version}
    For families WITHOUT variants: sick_perception_sdk/sensor_configuration/api/{family}/{version}
    """
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        return f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{metadata.device_type}/{version_dir}"
    else:
        return f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{version_dir}"


def _get_json_output_dir(metadata: DeviceMetadata) -> str:
    """
    Get the output directory for individual endpoint JSON headers.

    For families WITH variants: api/{family}/{variant}/{version}/
    For families WITHOUT variants: api/{family}/{version}/
    """
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        return os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, metadata.device_type, version_dir))
    else:
        return os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, version_dir))


def _generate_json_for_endpoint(endpoint: EndpointDescription, metadata: DeviceMetadata):
    """Generate individual JSON serialization header for a single endpoint."""
    out_dir = _get_json_output_dir(metadata)
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    class_name = endpoint.path.replace("/", "")
    file_name = f"{class_name}.nlohmann_json.g.hpp"
    full_file_name = os.path.join(out_dir, file_name)

    f = open(full_file_name, "w")
    _generate_file_header(f, file_name, metadata, endpoint)

    # Include the corresponding endpoint struct header
    include_prefix = _get_include_prefix(metadata)
    f.write(f"#include <{include_prefix}/{class_name}.g.hpp>\n")
    f.write(f"#include <nlohmann/json.hpp>\n")
    f.write(f"\n")

    _generate_namespaces_start(f, metadata)

    _generate_json_for_endpoint_method(f, endpoint, endpoint.get, class_name)
    _generate_json_for_endpoint_method(f, endpoint, endpoint.post, class_name)

    _generate_namespaces_end(f, metadata)

    f.close()


def _generate_json(endpoints: List[EndpointDescription], metadata: DeviceMetadata):
    """Generate JSON serialization headers for a specific device/version.

    This generates:
    1. Individual JSON headers per endpoint in api/json/{device}/{version}/{endpoint}.g.hpp
    2. An aggregate header that includes all individual headers in api/json/{device}/{version}.g.hpp
    """
    # Generate individual JSON headers per endpoint
    for endpoint in endpoints:
        _generate_json_for_endpoint(endpoint, metadata)

    # Generate aggregate JSON header that includes all individual endpoint JSON headers
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, metadata.device_type))
    else:
        out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family))

    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    file_name = f"{version_dir}.nlohmann_json.g.hpp"
    full_file_name = os.path.join(out_dir, file_name)
    print(f"ℹ️  Generating JSON aggregate header '{file_name}'...")
    f = open(full_file_name, "w")
    _generate_file_header(f, file_name, metadata, None)

    # Include all individual endpoint JSON headers
    json_include_prefix = _get_json_include_prefix(metadata)
    for endpoint in endpoints:
        class_name = endpoint.path.replace("/", "")
        f.write(f"#include <{json_include_prefix}/{class_name}.nlohmann_json.g.hpp>\n")
    f.write(f"\n")

    f.close()


def _generate_json_for_endpoint_method(f, endpoint: EndpointDescription, method: Optional[EndpointMethodDescription], class_name):
    if method is None:
        return

    class_name = class_name + "::" + method.method
    _generate_json_for_payload(f, endpoint, method.request_payload, class_name)
    _generate_json_for_payload(f, endpoint, method.response_payload, class_name)


def _generate_json_for_payload(f, endpoint: EndpointDescription, payload: Optional[ObjectDescription], class_name):
    if payload is None:
        return
    _generate_json_for_object(f, endpoint, payload, class_name)
    f.write("\n")


def _generate_version_include(endpoints: List[EndpointDescription], metadata: DeviceMetadata):
    """Generate version aggregate header that includes all endpoints for a specific version."""
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family, metadata.device_type))
    else:
        out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, metadata.family))

    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    file_name = f"{version_dir}.g.hpp"
    full_file_name = os.path.join(out_dir, file_name)
    print(f"ℹ️  Generating version include header in '{file_name}'...")
    f = open(full_file_name, "w")
    _generate_file_header(f, file_name, metadata, None)

    include_prefix = _get_include_prefix(metadata)
    for endpoint in endpoints:
        class_name = endpoint.path.replace("/", "")
        f.write(f"#include <{include_prefix}/{class_name}.g.hpp>\n")
    f.write(f"\n")

    f.close()


def _generate_file_header(f: TextIOWrapper, file_name: str, metadata: DeviceMetadata, endpoint: Optional[EndpointDescription]):
    f.write(f"/*\n")
    f.write(f"Copyright (c) {datetime.now().strftime('%Y')} SICK AG\n")
    f.write(f"SPDX-License-Identifier: MIT\n")
    f.write(f"*/\n")
    f.write(f"\n")

    device_desc = _get_namespace_name(metadata)
    f.write(f"/**\n")
    f.write(f" * @file {file_name} Sensor REST API payload definitions.\n")
    f.write(f" * @warning This file was generated for device '{device_desc}' version '{metadata.version}'.\n")
    f.write(f" * Do not edit manually!\n")

    if endpoint and endpoint.is_sopas_method:
        f.write(f" *\n")
        f.write(f" * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!\n")

    f.write(f" */\n")

    f.write(f"#pragma once\n")
    f.write(f"\n")


def _generate_includes(f: TextIOWrapper, includes: List[str]):
    for include in includes:
        f.write(f"{include}\n")
    f.write(f"\n")


def _generate_namespaces_start(f: TextIOWrapper, metadata: DeviceMetadata):
    """Generate namespace opening: sick::{namespace_name}::{version_namespace}::api::rest"""
    namespace_name = _get_namespace_name(metadata)
    version_namespace = _get_version_namespace(metadata)
    f.write(f"namespace sick::{namespace_name}::{version_namespace}::api::rest {{\n\n")


def _generate_namespaces_end(f: TextIOWrapper, metadata: DeviceMetadata):
    namespace_name = _get_namespace_name(metadata)
    version_namespace = _get_version_namespace(metadata)
    f.write(f"}} // namespace sick::{namespace_name}::{version_namespace}::api::rest\n")


def _generate_ctors(f: TextIOWrapper, name, obj: ObjectDescription, indent: int):
    indent_str = " " * indent
    # Generate default constructor (required for from_json)
    f.write(f"{indent_str}  {name}() = default;\n")
    f.write("\n")

    # Generate constructor with all fields as parameters
    f.write(f"{indent_str}  explicit {name}(")
    params = []
    for field in obj.fields:
        params.append(f"{field.type} {field.name}")
    f.write(", ".join(params))
    f.write(")\n")
    if obj.fields:
        f.write(f"{indent_str}    : ")
        inits = []
        for field in obj.fields:
            if field.type == "std::string" or field.type.startswith("NumericRange"):
                inits.append(f"{MEMBER_PREFIX}{field.name}(std::move({field.name}))")
            else:
                inits.append(f"{MEMBER_PREFIX}{field.name}({field.name})")
        f.write(", ".join(inits))
        f.write("\n")
    f.write(f"{indent_str}  {{}}\n")


def _generate_json_for_object(f: TextIOWrapper, endpoint: Optional[EndpointDescription], object: ObjectDescription, class_name: str):
    # Here the full class name with all namespaces is required because the to_json and from_json functions
    # are defined outside of the classes.
    class_name = class_name + "::" + object.class_name

    # First generate the to_json and from_json functions for all sub-objects.
    for sub_object in object.objects:
        _generate_json_for_object(f, None, sub_object, class_name)

    # Generate the to_json function to serialize the object to JSON.
    f.write(f"inline void to_json(nlohmann::ordered_json& j, {class_name} const& obj)\n")
    f.write(f"{{\n")

    # Special handling for objects at top level. If the object has only one field its value
    # must not be accessed by name because the name access is already done by the caller
    # (for accessing the first level inside the `data` field).
    is_sopas_method = endpoint.is_sopas_method if endpoint else False
    if len(object.fields) == 1 and object.parent is None and not is_sopas_method:
        field = object.fields[0]
        if field.type.startswith("NumericRange"):
            f.write(f"  j = obj.{MEMBER_PREFIX}{field.name}.value();\n")
        else:
            f.write(f"  j = obj.{MEMBER_PREFIX}{field.name};\n")
    else:
        f.write(f"  j = nlohmann::ordered_json{{\n")
        for field in object.fields:
            if field.type.startswith("NumericRange"):
                f.write(f'      {{"{field.name}", obj.{MEMBER_PREFIX}{field.name}.value()}},\n')
            else:
                f.write(f'      {{"{field.name}", obj.{MEMBER_PREFIX}{field.name}}},\n')
        f.write(f"  }};\n")
    f.write(f"}}\n")
    f.write(f"\n")

    # Generate the from_json function to deserialize the object from JSON.
    f.write(f"inline void from_json(const nlohmann::json& j, {class_name}& obj)\n")
    f.write(f"{{\n")
    # Special handling for objects at top level. If the object has only one field its value
    # must not be accessed by name because the name access is already done by the caller
    # (for accessing the first level inside the `data` field).
    if len(object.fields) == 1 and object.parent is None and not is_sopas_method:
        field = object.fields[0]
        f.write(f"  j.get_to(obj.{MEMBER_PREFIX}{field.name});\n")
    else:
        for field in object.fields:
            f.write(f'  j.at("{field.name}").get_to(obj.{MEMBER_PREFIX}{field.name});\n')
    f.write(f"}}\n")
    f.write(f"\n")


def _generate_object(f: TextIOWrapper, obj: ObjectDescription, indent: int):
    indent_str = " " * indent

    if obj.description:
        f.write(f"{indent_str}/**\n")
        prefix = "@brief"
        for line in obj.description.split("\n"):
            f.write(f"{indent_str} * {prefix} {line}\n")
            prefix = ""
        f.write(f"{indent_str} */\n")

    f.write(f"{indent_str}struct {obj.class_name}\n")
    f.write(f"{indent_str}{{\n")

    for enum in obj.enums:
        f.write(f"{indent_str}  enum class {enum.class_name}\n")
        f.write(f"{indent_str}  {{\n")
        for field in enum.fields:
            f.write(f"{indent_str}    {field.name} = {field.type},\n")
        f.write(f"{indent_str}  }};\n")
        f.write("\n")

    for sub_obj in obj.objects:
        _generate_object(f, sub_obj, indent + 2)
        f.write("\n")

    _generate_ctors(f, obj.class_name, obj, indent)
    f.write("\n")

    for field in obj.fields:
        f.write(f"{indent_str}  {field.type} {MEMBER_PREFIX}{field.name};\n")
    f.write(f"{indent_str}}};\n")


def _collect_includes(obj: ObjectDescription, includes: Set[str]) -> None:
    """
    Flatten all includes of our object tree: recursively collect all includes from the object
    and its sub-objects.
    """
    includes.update(obj.includes)
    for sub_obj in obj.objects:
        _collect_includes(sub_obj, includes)


def generate_aggregate_headers(all_endpoints: List[Tuple[List[EndpointDescription], DeviceMetadata]]):
    """
    Generate aggregate headers for variants/families with the `latest` namespace alias.

    For families WITH variants: generates api/{family}/{variant}.g.hpp
    For families WITHOUT variants: generates api/{family}.g.hpp

    Each header includes all firmware version headers and defines `latest` alias
    pointing to the semantically highest version.
    """
    # Group by namespace_name (device_type: variant for families with variants, family for others)
    grouped: Dict[str, List[DeviceMetadata]] = defaultdict(list)
    for _, metadata in all_endpoints:
        grouped[_get_namespace_name(metadata)].append(metadata)

    for namespace_name, metadata_list in grouped.items():
        # Sort by semantic version to determine latest
        sorted_metadata = sorted(metadata_list, key=lambda m: Version(m.version))
        latest_metadata = sorted_metadata[-1]

        # Determine output path
        # For variants: api/{family}/{variant}.g.hpp
        # For non-variants: api/{family}/{family}.g.hpp
        if _is_variant(latest_metadata):
            out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, latest_metadata.family))
            file_name = f"{latest_metadata.device_type}.g.hpp"
        else:
            out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, latest_metadata.family))
            file_name = f"{latest_metadata.family}.g.hpp"

        if not os.path.exists(out_dir):
            os.makedirs(out_dir)

        full_file_name = os.path.join(out_dir, file_name)
        version_namespace = _get_version_namespace(latest_metadata)
        print(f"ℹ️  Generating aggregate header '{file_name}' with latest = {version_namespace}...")

        with open(full_file_name, "w") as f:
            # File header
            f.write(f"/*\n")
            f.write(f"Copyright (c) {datetime.now().strftime('%Y')} SICK AG\n")
            f.write(f"SPDX-License-Identifier: MIT\n")
            f.write(f"*/\n")
            f.write(f"\n")
            f.write(f"/**\n")
            f.write(f" * @file {file_name} Aggregate header for {namespace_name}.\n")
            f.write(f" * @warning This file was auto-generated. Do not edit manually!\n")
            f.write(f" */\n")
            f.write(f"#pragma once\n")
            f.write(f"\n")

            # Include all version headers (sorted by version)
            for metadata in sorted_metadata:
                version_dir = metadata.version.replace(".", "_")
                if _is_variant(metadata):
                    include_path = f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{metadata.device_type}/{version_dir}.g.hpp"
                else:
                    include_path = f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{version_dir}.g.hpp"
                f.write(f"#include <{include_path}>\n")

            f.write(f"\n")

    # Also generate aggregate JSON headers
    _generate_aggregate_json_headers(all_endpoints)


def _generate_aggregate_json_headers(all_endpoints: List[Tuple[List[EndpointDescription], DeviceMetadata]]):
    """Generate aggregate JSON headers matching the pattern of API headers."""
    # Group by namespace_name (device_type)
    grouped: Dict[str, List[DeviceMetadata]] = defaultdict(list)
    for _, metadata in all_endpoints:
        grouped[_get_namespace_name(metadata)].append(metadata)

    for namespace_name, metadata_list in grouped.items():
        sorted_metadata = sorted(metadata_list, key=lambda m: Version(m.version))
        latest_metadata = sorted_metadata[-1]

        # Determine output path
        if _is_variant(latest_metadata):
            out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, latest_metadata.family))
            file_name = f"{latest_metadata.device_type}.nlohmann_json.g.hpp"
        else:
            out_dir = os.path.abspath(os.path.join(DATA_OBJECT_OUT_DIR, latest_metadata.family))
            file_name = f"{latest_metadata.family}.nlohmann_json.g.hpp"

        if not os.path.exists(out_dir):
            os.makedirs(out_dir)

        full_file_name = os.path.join(out_dir, file_name)
        print(f"ℹ️  Generating aggregate JSON header '{file_name}'...")

        with open(full_file_name, "w") as f:
            f.write(f"/*\n")
            f.write(f"Copyright (c) {datetime.now().strftime('%Y')} SICK AG\n")
            f.write(f"SPDX-License-Identifier: MIT\n")
            f.write(f"*/\n")
            f.write(f"\n")
            f.write(f"/**\n")
            f.write(f" * @file {file_name} Aggregate JSON header for {namespace_name}.\n")
            f.write(f" * @warning This file was auto-generated. Do not edit manually!\n")
            f.write(f" */\n")
            f.write(f"#pragma once\n")
            f.write(f"\n")

            # Include all version JSON headers
            for metadata in sorted_metadata:
                version_dir = metadata.version.replace(".", "_")
                if _is_variant(metadata):
                    include_path = f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{metadata.device_type}/{version_dir}.nlohmann_json.g.hpp"
                else:
                    include_path = f"sick_perception_sdk/sensor_configuration/api/{metadata.family}/{version_dir}.nlohmann_json.g.hpp"
                f.write(f"#include <{include_path}>\n")

            f.write(f"\n")
