from io import TextIOWrapper
import os
import glob
from typing import List, Optional, Set, Dict, Tuple
from datetime import datetime
from collections import defaultdict

from packaging.version import Version

from objects import DeviceMetadata, EndpointDescription, EndpointMethodDescription, ObjectDescription, FieldDescription, EnumDescription

DATA_OBJECT_OUT_DIR = os.path.join("src/sensor_configuration/include/sick_perception_sdk/sensor_configuration/api")
MEMBER_PREFIX = "_"

# Output directory for generated Endpoints implementation (.cpp) files and the CMake source manifest.
GENERATED_SRC_OUT_DIR = os.path.join("src/sensor_configuration/generated")


def clean_generated_files():
    """Delete all previously generated files (*.g.*) from the output directories."""
    removed = 0
    for root_dir in (DATA_OBJECT_OUT_DIR, GENERATED_SRC_OUT_DIR):
        for file_path in glob.glob(os.path.join(root_dir, "**", "*.g.*"), recursive=True):
            os.remove(file_path)
            removed += 1
    print(f"ℹ️  Cleaned up {removed} previously generated file(s).")


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
            if field.type == "std::string":
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


# =============================================================================
# Endpoints class generation (typed per-device/version facade over SopasClient)
# =============================================================================


def _lower_camel(name: str) -> str:
    """Lower-case the first character of an endpoint name to form a SOPAS method name."""
    if not name:
        return name
    return name[0].lower() + name[1:]


def _upper_camel(name: str) -> str:
    """Upper-case the first character of an endpoint name so 'get'/'set' prefixes read as camelCase."""
    if not name:
        return name
    return name[0].upper() + name[1:]


def _single_field(payload: Optional[ObjectDescription]) -> Optional[FieldDescription]:
    """
    Return the sole field of a payload when it wraps exactly one scalar value.

    This is used to unwrap single-field payloads so callers can use the value directly instead of
    reaching through a struct member (e.g. `getFirmwareVersion()` returns the string directly instead
    of a struct with a single `_FirmwareVersion` member). The sole field is unwrapped regardless of
    its kind: scalar, nested enum, or nested struct (the facade returns the field type via
    `decltype`).
    """
    if payload is None:
        return None
    if len(payload.fields) == 1:
        return payload.fields[0]
    return None


def _get_generated_src_subdir(metadata: DeviceMetadata) -> str:
    """
    Relative sub-directory (below GENERATED_SRC_OUT_DIR) for the generated Endpoints .cpp file.

    For families WITH variants: api/{family}/{variant}/{version}
    For families WITHOUT variants: api/{family}/{version}
    """
    version_dir = metadata.version.replace(".", "_")
    if _is_variant(metadata):
        return os.path.join("api", metadata.family, metadata.device_type, version_dir)
    else:
        return os.path.join("api", metadata.family, version_dir)


def _endpoint_source_variable_name(metadata: DeviceMetadata) -> str:
    """CMake manifest variable suffix, e.g. picoScan150_v2_3_1."""
    return f"{_get_namespace_name(metadata)}_{_get_version_namespace(metadata)}"


def _endpoint_methods(endpoint: EndpointDescription) -> List[Tuple[str, str]]:
    """
    Compute the (declaration, definition-body) pairs for a single endpoint.

    Each tuple is (declaration_without_semicolon, one_line_forward_call). The declaration is emitted
    verbatim in the header (with a trailing ';') and as the signature in the .cpp (with the method
    name qualified by 'Endpoints::').
    """
    methods: List[Tuple[str, str]] = []
    name = endpoint.class_name
    payload = f"api::rest::{name}"

    if endpoint.is_sopas_method:
        method_name = _lower_camel(name)
        has_request = endpoint.post is not None and endpoint.post.request_payload is not None
        has_response = endpoint.post is not None and endpoint.post.response_payload is not None

        response_field = _single_field(endpoint.post.response_payload) if has_response else None
        if response_field is not None:
            response_member = f"{MEMBER_PREFIX}{response_field.name}"
            response_type = f"decltype({payload}::Post::Response::{response_member})"
        else:
            response_type = f"{payload}::Post::Response"

        request_field = _single_field(endpoint.post.request_payload) if has_request else None
        if request_field is not None:
            request_member = f"{MEMBER_PREFIX}{request_field.name}"
            request_param = f"decltype({payload}::Post::Request::{request_member}) const& value"
            request_arg = f"{payload}::Post::Request{{value}}"
        else:
            request_param = f"{payload}::Post::Request const& request"
            request_arg = "request"

        if has_request and has_response:
            decl = f"auto {method_name}({request_param}) const -> {response_type}"
            call = f"m_sopasClient->invokeMethod<{payload}>({request_arg})"
            body = f"return {call}{'.' + response_member if response_field is not None else ''};"
        elif has_request and not has_response:
            decl = f"void {method_name}({request_param}) const"
            body = f"m_sopasClient->invokeMethodWithoutResponse<{payload}>({request_arg});"
        elif not has_request and has_response:
            decl = f"auto {method_name}() const -> {response_type}"
            call = f"m_sopasClient->invokeMethodWithoutRequest<{payload}>()"
            body = f"return {call}{'.' + response_member if response_field is not None else ''};"
        else:
            decl = f"void {method_name}() const"
            body = f"m_sopasClient->invokeMethodWithoutRequestAndResponse<{payload}>();"
        methods.append((decl, body))
        return methods

    # Non-method endpoint: variable read and/or write.
    if endpoint.get is not None and endpoint.get.response_payload is not None:
        field = _single_field(endpoint.get.response_payload)
        if field is not None:
            member = f"{MEMBER_PREFIX}{field.name}"
            decl = f"auto get{_upper_camel(name)}() const -> decltype({payload}::Get::Response::{member})"
            body = f"return m_sopasClient->readVariable<{payload}>().{member};"
        else:
            decl = f"auto get{_upper_camel(name)}() const -> {payload}::Get::Response"
            body = f"return m_sopasClient->readVariable<{payload}>();"
        methods.append((decl, body))

    if endpoint.post is not None and endpoint.post.request_payload is not None:
        request_field = _single_field(endpoint.post.request_payload)
        if request_field is not None:
            request_member = f"{MEMBER_PREFIX}{request_field.name}"
            request_type = f"decltype({payload}::Post::Request::{request_member})"
            decl = f"void set{_upper_camel(name)}({request_type} const& value) const"
            body = f"m_sopasClient->writeVariable<{payload}>({payload}::Post::Request{{value}});"
        else:
            decl = f"void set{_upper_camel(name)}({payload}::Post::Request const& request) const"
            body = f"m_sopasClient->writeVariable<{payload}>(request);"
        methods.append((decl, body))

    return methods


def generate_endpoints(endpoints: List[EndpointDescription], metadata: DeviceMetadata):
    """
    Generate the typed `Endpoints` facade (header + implementation) for a device/version.

    - `Endpoints.g.hpp` (in the include tree) declares one method per endpoint. It includes only the
      plain payload struct aggregate (no nlohmann/json) and forward-declares `SopasClient`.
    - `Endpoints.g.cpp` (in the generated source tree) includes `SopasClient.hpp` and the nlohmann
      serializer aggregate, defining every method as a one-line forward to the engine. This keeps the
      nlohmann/json dependency private to the SDK library build.
    """
    namespace_name = _get_namespace_name(metadata)
    version_namespace = _get_version_namespace(metadata)
    version_dir = metadata.version.replace(".", "_")
    include_prefix = _get_include_prefix(metadata)
    # The version aggregate headers live next to (not inside) the per-version include directory,
    # e.g. api/{family}[/{variant}]/{version}.g.hpp.
    aggregate_prefix = include_prefix.rsplit("/", 1)[0]

    # Collect method declarations/definitions across all endpoints, sorted alphabetically by
    # method name so the generated output has a stable, readable ordering.
    all_methods: List[Tuple[str, str]] = []
    for endpoint in endpoints:
        all_methods.extend(_endpoint_methods(endpoint))
    all_methods.sort(key=lambda method: _method_name(method[0]))

    # ---- Header (Endpoints.g.hpp) in the include tree ------------------------
    header_out_dir = _get_output_dir(metadata)
    if not os.path.exists(header_out_dir):
        os.makedirs(header_out_dir)

    header_name = "Endpoints.g.hpp"
    print(f"ℹ️  Generating '{header_name}' for {namespace_name} {version_namespace}...")
    with open(os.path.join(header_out_dir, header_name), "w") as f:
        _generate_file_header(f, header_name, metadata, None)

        f.write("#include <sick_perception_sdk/common/export.hpp>\n")
        f.write("#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>\n")
        f.write(f"#include <{aggregate_prefix}/{version_dir}.g.hpp>\n")
        f.write("#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>\n")
        f.write("\n")
        f.write("#include <memory>\n")
        f.write("#include <string>\n")
        f.write("\n")

        f.write("namespace sick {\n")
        f.write("class SopasClient;\n")
        f.write("} // namespace sick\n")
        f.write("\n")

        f.write(f"namespace sick::{namespace_name}::{version_namespace} {{\n\n")

        f.write("/**\n")
        f.write(" * @brief Typed access to all documented REST endpoints of this device/version.\n")
        f.write(" *\n")
        f.write(" * Each method forwards to the SopasClient engine. The nlohmann/json dependency is kept private\n")
        f.write(" * to the SDK library build, so including this header does not pull in nlohmann/json.\n")
        f.write(" */\n")
        f.write("class SDK_EXPORT Endpoints\n{\npublic:\n")
        f.write("  explicit Endpoints(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);\n\n")
        for decl, _ in all_methods:
            f.write(f"  {decl};\n")
        f.write("\nprotected:\n")
        f.write("  std::unique_ptr<SopasClient> m_sopasClient;\n")
        f.write("};\n\n")

        f.write(f"}} // namespace sick::{namespace_name}::{version_namespace}\n")

    # ---- Implementation (Endpoints.g.cpp) in the generated source tree -------
    src_subdir = _get_generated_src_subdir(metadata)
    src_out_dir = os.path.abspath(os.path.join(GENERATED_SRC_OUT_DIR, src_subdir))
    if not os.path.exists(src_out_dir):
        os.makedirs(src_out_dir)

    src_name = "Endpoints.g.cpp"
    print(f"ℹ️  Generating '{src_name}' for {namespace_name} {version_namespace}...")
    with open(os.path.join(src_out_dir, src_name), "w") as f:
        f.write("/*\n")
        f.write(f"Copyright (c) {datetime.now().strftime('%Y')} SICK AG\n")
        f.write("SPDX-License-Identifier: MIT\n")
        f.write("*/\n\n")
        f.write("/**\n")
        f.write(f" * @file {src_name} Generated Endpoints implementation.\n")
        f.write(f" * @warning This file was generated for device '{namespace_name}' version '{metadata.version}'.\n")
        f.write(" * Do not edit manually!\n")
        f.write(" */\n\n")

        f.write(f"#include <{include_prefix}/Endpoints.g.hpp>\n\n")
        f.write("#include <sick_perception_sdk/sensor_configuration/SopasClientImpl.hpp>\n")
        f.write("#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>\n")
        f.write(f"#include <{aggregate_prefix}/{version_dir}.nlohmann_json.g.hpp>\n")
        f.write("#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>\n")
        f.write("\n")
        f.write("#include <memory>\n")
        f.write("#include <utility>\n")
        f.write("\n")

        f.write(f"namespace sick::{namespace_name}::{version_namespace} {{\n\n")

        f.write("Endpoints::Endpoints(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)\n")
        f.write("  : m_sopasClient(std::make_unique<SopasClient>(httpClient, userLevel, password))\n")
        f.write("{}\n\n")

        for decl, body in all_methods:
            # Qualify the method name with 'Endpoints::'. The declaration starts with the return type,
            # so split off the first token(s) up to the method name. We insert 'Endpoints::' before the
            # first '(' identifier by replacing the leading "auto <name>(" / "void <name>(" pattern.
            qualified = _qualify_method_decl(decl)
            f.write(f"{qualified}\n{{\n  {body}\n}}\n\n")

        f.write(f"}} // namespace sick::{namespace_name}::{version_namespace}\n")


def _method_name(decl: str) -> str:
    """
    Extract the bare method name from a member declaration.

    Examples:
      "auto getEtherIPAddress() const -> ..."  -> "getEtherIPAddress"
      "void setEtherIPAddress(... ) const"      -> "setEtherIPAddress"
    """
    head = decl[: decl.index("(")]
    return head[head.rindex(" ") + 1 :]


def _qualify_method_decl(decl: str) -> str:
    """
    Turn a member declaration into an out-of-class definition signature by inserting 'Endpoints::'
    before the method name.

    Examples:
      "auto getEtherIPAddress() const -> ..."  -> "auto Endpoints::getEtherIPAddress() const -> ..."
      "void setEtherIPAddress(... ) const"      -> "void Endpoints::setEtherIPAddress(... ) const"
    """
    paren = decl.index("(")
    head = decl[:paren]
    tail = decl[paren:]
    # head is like "auto getEtherIPAddress" or "void setEtherIPAddress".
    space = head.rindex(" ")
    return f"{head[:space]} Endpoints::{head[space + 1:]}{tail}"


def generate_sources_manifest(all_endpoints: List[Tuple[List[EndpointDescription], DeviceMetadata]]):
    """
    Emit the CMake manifest that lists every generated Endpoints .cpp file.

    Defines one source-list variable per device/version plus an aggregate `_ALL` variable so the
    build can select devices individually or compile all of them.
    """
    out_dir = os.path.abspath(GENERATED_SRC_OUT_DIR)
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    manifest_path = os.path.join(out_dir, "generated_sources.cmake")
    print(f"ℹ️  Generating CMake source manifest '{manifest_path}'...")

    per_device_vars: List[str] = []
    lines: List[str] = []
    lines.append("# AUTO-GENERATED by generate_openapi.sh — do not edit.\n")
    lines.append("\n")

    for _, metadata in sorted(all_endpoints, key=lambda item: _endpoint_source_variable_name(item[1])):
        var_suffix = _endpoint_source_variable_name(metadata)
        var_name = f"SENSOR_CONFIGURATION_GENERATED_SOURCES_{var_suffix}"
        rel_path = os.path.join(_get_generated_src_subdir(metadata), "Endpoints.g.cpp").replace(os.sep, "/")
        lines.append(f"set({var_name}\n")
        lines.append(f'  "${{CMAKE_CURRENT_LIST_DIR}}/{rel_path}")\n')
        lines.append("\n")
        per_device_vars.append(var_name)

    lines.append("set(SENSOR_CONFIGURATION_GENERATED_SOURCES_ALL\n")
    for var_name in per_device_vars:
        lines.append(f"  ${{{var_name}}}\n")
    lines.append(")\n")

    with open(manifest_path, "w") as f:
        f.writelines(lines)
