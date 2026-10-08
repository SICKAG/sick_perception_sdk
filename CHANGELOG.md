# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.0.0]

This release includes many breaking changes to make the API of the SDK more consistent and resolve performance issues.

### Breaking Changes in library compact_format

#### `ScanData`

- Changed the data layout of `compact::scan_data::ScanData` to be organized as structure of arrays instead of array of structures. This change improves the cache efficiency and performance when processing the scan data, but it requires changes in the code that accesses the `ScanData` structure.
- Moved `segmentIndex` and `frameSequenceNumber` from `ScanData::Module` to `ScanData`.
- Moved `senderSerialNumber` from `ScanData::Module` to `compact::TelegramHeader`.
- Removed `ScanData::Module::numberOfRows`. Use `Module::rowMetaData::size()` instead.
- Removed `ScanData::distanceScalingFactor`, `ScanData::numberOfBytesOfNextModule`, and `ScanData::checksum` as they were exclusively required for parsing.
- Removed `ScanData::Module::echoContent` and `ScanData::Module::beamContent`. Check the data vectors for emptiness directly. For examples, use `ScanData::Module::distances::empty()` to check whether there are any distance values.
- Beam properties are now represented by a `BitField` instead of a plain integer.
- `sick::compact::scan_data::getBeamProperty()` was renamed to `sick::compact::scan_data::getBeamProperties()`.

#### `EncoderData`

- Moved `EncoderData::Payload::senderId` to `EncoderData::telegramHeader::senderSerialNumber`.
- Moved `EncoderData::Payload::frameSequenceNumber` to `EncoderData::frameSequenceNumber`.
- Moved `EncoderData::Payload::tickCounter` to `EncoderData::tickCount`.
- Moved `EncoderData::Payload::tickCounterReference1` to `EncoderData::tickCountAtReferenceSignal1`.
- Moved `EncoderData::Payload::tickCounterReference2` to `EncoderData::tickCountAtReferenceSignal2`.
- Moved `EncoderData::Payload::speed` to `EncoderData::speed`.
- Moved `EncoderData::Payload::tickCounterTimestamp` to `EncoderData::tickCountTimestamp`.
- Moved `EncoderData::Payload::timestampReference1` to `EncoderData::timestampOfReferenceSignal1`.
- Moved `EncoderData::Payload::timestampReference2` to `EncoderData::timestampOfReferenceSignal2`.
- Removed `EncoderData::Payload::checksum` as it was exclusively required for parsing.

#### `MultiScan200Data`

- Changed the type of `SegmentMetaData::numberOfSegmentsPerFrame`, `SegmentMetaData::numberOfColumnsInSegment`, `SegmentMetaData::numberOfColumnsInFrame`, `SegmentMetaData::numberOfRows`, `SegmentMetaData::numberOfEchoes`, `SegmentMetaData::numberOfAmbientLightRows`, `SegmentMetaData::numberOfInterlaceSteps`, `SegmentMetaData::currentInterlaceIndex` to `std::size_t`.
- Removed `SegmentMetaData::distanceScalingFactor` and `SegmentMetaData::reservedSize`, `SegmentMetaData::echoDataContent` and `kSizeOfAmbientLightPixel` as they were exclusively required for parsing.

#### `PointCloud`

- Renamed `LayerId` to `LayerIndex` (see `PointCloudAttributes.hpp`):
- Point cloud properties are now represented by an enum (`sick::point_cloud::Properties`) instead of the boolean `Is<...>`/`Has<...>` properties.
- Protocol- and device-specific properties are mapped to the `sick::point_cloud::Properties` so the point cloud always uses a standardized properties interface.
- Removed `Density` enum. With LiDAR sensors it is very unlikely to get an (organized) point cloud without any invalid points so the flag would almost never be AllPointsValid.

#### Misc

- Removed `ImuData::header` and `ImuData::checksum` as they were exclusively required for parsing.
- Changed the type of `AmbientLightData::numberOfLayers` and `AmbientLightData::numberOfColumns` to `std::size_t`.
- Removed `TelegramHeader::startOfFrame`.
- Moved `TelegramHeader::telegramType`, `TelegramHeader::telegramVersion`, and `TelegramHeader::payloadLength` to `TelegramHeaderWireInfo`.
- Removed `TelegramHeaderWithSenderSerialNumber`.
- Moved `TelegramHeaderWithSenderSerialNumber::senderSerialNumber` to `TelegramHeader`.

### Breaking Changes in library common

- Removed the `std::to_string(...)` overloads for the quantity types (`Acceleration`, `Angle`, `AngularVelocity`, `Distance`, `Duration`, `Speed`, `Temperature`, `Timestamp`). Use the stream `operator<<` (or the type's own accessors) instead.

### Breaking Changes in sensor_configuration

- Reworked the `IHttpClient` interface: the separate `get()` and `post()` methods were replaced by a single content-type-aware `send(HttpRequest const&) -> HttpResponse`. Custom `IHttpClient` implementations must be updated accordingly.
- Removed the internal REST layer `RestClient` and `PostRequest` as well as the `SensorConfigurator` base class. Configurators now derive from the generated `Endpoints` class and use `SopasClient` internally.
- Removed the `*Access` helper objects (e.g. `AngleRangeFilterAccess`, `CuboidFilterAccess`, `DistanceFilterAccess`, ...) and the generic `GetAccess`/`EnableAccess`/`DisableAccess`/`IsEnabledAccess` model. Configuration is now performed through dedicated methods on the respective `Configurator`.
- Removed the `api/FieldEvaluationContour.hpp` and `api/SensorPosition.hpp` helper types together with `getSensorPosition()` and `setSensorPosition()`.
- Replaced `getSystemTime()`/`setSystemTime()` with `getSystemTimeOfSensor()`.
- Replaced the `UserLevelToStringMap` lookup table with a `toString(UserLevel)` function.
- Changed the picoScan150 configurator namespace from `sick::picoScan150::v2_3_1` to `sick::picoScan150::v2_3_3`.
- `NumericRange`'s `from_json` is now templated on the JSON type; the public header no longer includes `<nlohmann/json.hpp>`.

### Added

- Support for multiScan200 including Compact telegram type 6.
- Function `sizeOfSubByteArray` to `SubByteArrayConverter`.
- enum to store the encoding of `AmbientLightData`.
- class `CompactParserContext`.
- explicit protocol descriptions for compact telegrams in
  - `compact::scan_data::telegram`
  - `compact::imu::telegram`
  - `compact::ambient_light::telegram`
  - `compact::encoder::telegram`
  - `compact::multiscan200::telegram`
- Column index as field in the point cloud.

### Fixed

- Bug that organized point clouds could be converted when any of the following filters was configured in the `PointCloudConfiguration`: `selectedEchos`, `selectedLayers`, `azimuth`, `elevation`.

## [1.0.1]

### Fixed

- Fixed a bug where linking failed by setting `-DHTTPLIB_USE_ZSTD_IF_AVAILABLE=OFF` when building `cpp-httplib` with the install scripts.

## [1.0.0]

First release of the sick_perception_sdk package. This release includes the following features:

- Initial implementation of the SDK components for interacting with SICK sensors.
- Basic documentation and examples for using the sick_perception_sdk.
- Support for the following SICK LiDAR sensors: picoScan100, multiScan100, and LRS4000.
