from dataclasses import dataclass
from typing import List, Optional


@dataclass(frozen=True)
class DeviceMetadata:
    """Metadata extracted from schema directory structure and YAML file."""

    family: str  # e.g., "picoScan100", "multiScan100"
    device_type: str  # e.g., "picoScan150" for variants, or family name if no variant
    version: str  # e.g., "2.2.1" from info/version in YAML


class EnumFieldDescription:
    def __init__(self, name: str, type: str):
        self.name = name
        self.type = type


class EnumDescription:
    def __init__(self, class_name: str):
        self.class_name = class_name
        self.fields: List[EnumFieldDescription] = []


class FieldDescription:
    def __init__(self, name: str, type: str):
        self.name = name
        self.type = type


class ObjectDescription:
    def __init__(self, class_name: str, parent):
        self.class_name = class_name
        self.parent = parent
        self.fields: List[FieldDescription] = []
        self.enums: List[EnumDescription] = []
        self.objects: List[ObjectDescription] = []
        self.includes: List[str] = []
        self.description: str = ""


class EndpointMethodDescription:
    def __init__(self, method: str, description: str | None, request_payload: Optional[ObjectDescription], response_payload: Optional[ObjectDescription]):
        self.method = method
        self.description = description
        self.request_payload = request_payload
        self.response_payload = response_payload


class EndpointDescription:
    def __init__(self, path: str):
        self.path = path
        self.class_name = path.replace("/", "")  # Name of the C++ class representing this endpoint
        self.get: Optional[EndpointMethodDescription] = None
        self.post: Optional[EndpointMethodDescription] = None
        self.is_sopas_method = False
        self.tags: List[str] = []  # Tags from OpenAPI spec for grouping
