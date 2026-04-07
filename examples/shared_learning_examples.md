# Shared Learning Examples

- [Configuration](#configuration)
- [Data streaming UDP (picoScan100, multiScan100)](#data-streaming-udp-picoscan100-multiscan100)
- [Data streaming TCP (LRS4000)](#data-streaming-tcp-lrs4000)
- [Data streaming ROI](#data-streaming-roi)
- [Low-level streaming UDP (picoScan100, multiScan100)](#low-level-streaming-udp-picoscan100-multiscan100)
- [Low-level streaming TCP (LRS4000)](#low-level-streaming-tcp-lrs4000)
- [Multiple devices (picoScan100, multiScan100)](#multiple-devices-picoscan100-multiscan100)
- [Object detection (picoScan100, LRS4000, multiScan100)](#object-detection-picoscan100-lrs4000-multiscan100)
- [Segmented data (picoScan100, multiScan100)](#segmented-data-picoscan100-multiscan100)
- [Write to PCD files (picoScan100, multiScan100)](#write-to-pcd-files-picoscan100-multiscan100)
- [Change IP address](#change-ip-address)
- [Download and import configuration (picoScan100, multiScan100)](#download-and-import-configuration-picoscan100-multiscan100)
- [More device configuration](#more-device-configuration)

## Configuration

This example [shared/configuration.cpp](shared/configuration.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints the following information from the connected device: device type, firmware version, location name, order number, serial number, system time, and device IP address
- Reads operational hours from the device
- Sets echo filter to LastEcho
- Configures angle range filter (start: -90°, stop: 90°, beam increment: 1)
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Expected device configuration: Factory defaults, licenses for used functions available

## Data streaming UDP (picoScan100, multiScan100)

This example [shared/data_streaming_udp.cpp](shared/data_streaming_udp.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Enables IMU data streaming (UDP) to IP address `192.168.0.100`, port `7503`
- Enables encoder data streaming (UDP) to IP address `192.168.0.100`, port `7504`
- Receives and prints metadata for frame point cloud data, IMU data, and encoder data
- Expected device configuration: Factory defaults, licenses for used functions available

## Data streaming TCP (LRS4000)

This example [shared/data_streaming_tcp.cpp](shared/data_streaming_tcp.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Sets the measurement data format to Compact
- Receives and prints metadata for frame point cloud data
- Expected device configuration: Factory defaults, licenses for used functions available

## Data streaming ROI

This example [shared/data_streaming_roi.cpp](shared/data_streaming_roi.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Configures region of interest (ROI) filters for azimuth (-1° to 1°) and elevation (-1° to 1°)
- Receives and prints all points within the defined ROI
- Expected device configuration: Factory defaults, licenses for used functions available

## Low-level streaming UDP (picoScan100, multiScan100)

This example [shared/low_level_streaming_udp.cpp](shared/low_level_streaming_udp.cpp)

- Listens for UDP packets on port `2115` (format Compact)
- Receives raw data from the socket using a reusable buffer
- Parses and validates Compact telegrams from the received data
- Prints the number of modules in each received scan data frame
- Demonstrates low-level handling of UDP streaming data without using high-level device configuration APIs
- Expected device configuration: Device streaming Compact data on UDP port 2115

## Low-level streaming TCP (LRS4000)

This example [shared/low_level_streaming_tcp.cpp](shared/low_level_streaming_tcp.cpp)

- Establishes a TCP connection to the device using the specified IP address or the default IP address (192.168.0.1 if no IP is specified) on port `2115`
- Receives raw data from the socket using a reusable buffer
- Extracts Compact telegrams from the received data stream using StreamExtractor
- Parses and validates the scan data telegrams
- Prints the number of modules in each received scan data frame
- Demonstrates low-level handling of TCP streaming data without using high-level device configuration APIs
- Expected device configuration: Device streaming Compact data on TCP port 2115

## Multiple devices (picoScan100, multiScan100)

This example [shared/multiple_devices.cpp](shared/multiple_devices.cpp)

- Establishes connections to both devices (192.168.0.1, 192.168.0.2)
- Reads and prints the IP addresses from both connected devices
- Sets the measurement data output format to _Compact_
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, ports `2115` and `2116`
- Prints metadata for frame point cloud data from both devices
- Expected device configuration: Factory defaults, licenses for used functions available

## Object detection (picoScan100, LRS4000, multiScan100)

This example [shared/object_detection.cpp](shared/object_detection.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints evaluation group states for all active fields
- Reads and prints evaluation field states and results
- Reads field evaluation contours (field points and z-limits)
- Scales all x-y coordinates of field contours by a factor of 0.5
- Writes the modified field contours back to the device
- Expected device configuration: At least one field stored in object detection, object detection license available

## Segmented data (picoScan100, multiScan100)

This example [shared/segmented_data.cpp](shared/segmented_data.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints the following information from the connected device: product name, part number, serial number, firmware version, system time, and device IP address
- Sets the measurement data output format to _Compact_
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Prints metadata for segmented measurement data
- Expected device configuration: Factory defaults, licenses for used functions available

## Write to PCD files (picoScan100, multiScan100)

This example [shared/write_to_pcd_files.cpp](shared/write_to_pcd_files.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints the following information from the connected device: product name, part number, serial number, firmware version, system time, and device IP address
- Sets the measurement data output format to _Compact_
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Creates a new PCD file with the latest frame every second
- Expected device configuration: Factory defaults, licenses for used functions available

## Change IP address

This example [shared/change_ip_address.cpp](shared/change_ip_address.cpp)

- Establishes a connection to the device using the initial IP address (192.168.0.1)
- Reads and prints the current IP address configuration
- Configures new static IP settings (IP address: 192.168.0.2, subnet mask: 255.255.255.0, gateway: 0.0.0.0)
- Applies the IP configuration changes and waits for the sensor
- Reconnects to the device using the new IP address (192.168.0.2)
- Expected device configuration: Factory defaults

## Download and import configuration (picoScan100, multiScan100)

This example [shared/download_and_import_config.cpp](shared/download_and_import_config.cpp)

- Establishes a connection to the device using the specified IP address or the default IP address (192.168.0.1 if no IP is specified)
- Creates a parameter backup on the device
- Downloads the backup and saves it to a local file
- Changes the LocationName on the device to later verify the restore
- Uploads the previously saved backup
- Restores the parameter backup on the device
- Persists the restored parameters
- Verifies that the LocationName has been restored to its original value
- Expected device configuration: Factory defaults

## More device configuration

All configuration and status interactions with the sensor are based on the sensors REST APIs. A summary of all available sensor configuration via the SDK can be found here [doc/device_configuration_overview.md](../doc/device_configuration_overview.md).
