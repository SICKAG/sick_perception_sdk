# Shared Learning Examples

- [Print SDK version](#print-sdk-version)
- [Configuration](#configuration)
- [Data streaming UDP (picoScan100, multiScan100)](#data-streaming-udp-picoscan100-multiscan100)
- [Data streaming UDP multicast (picoScan100, multiScan100)](#data-streaming-udp-multicast-picoscan100-multiscan100)
- [Data streaming TCP (LRS4000, multiScan200)](#data-streaming-tcp-lrs4000-multiscan200)
- [Low-level streaming UDP (picoScan100, multiScan100)](#low-level-streaming-udp-picoscan100-multiscan100)
- [Low-level streaming TCP (LRS4000, multiScan200)](#low-level-streaming-tcp-lrs4000-multiscan200)
- [Multiple devices (picoScan100, multiScan100)](#multiple-devices-picoscan100-multiscan100)
- [Object detection (picoScan100, LRS4000, multiScan100)](#object-detection-picoscan100-lrs4000-multiscan100)
- [Segmented data (picoScan100, multiScan100)](#segmented-data-picoscan100-multiscan100)
- [Write to PCD files (picoScan100, multiScan100)](#write-to-pcd-files-picoscan100-multiscan100)
- [Change IP address](#change-ip-address)
- [Download and import configuration (picoScan100, multiScan100, multiScan200)](#download-and-import-configuration-picoscan100-multiscan100-multiscan200)
- [Firmware update (picoScan100, multiScan100, multiScan200)](#firmware-update-picoscan100-multiscan100-multiscan200)
- [More device configuration](#more-device-configuration)

## Print SDK version

This example [shared/print_version.cpp](shared/print_version.cpp)

- Prints the version of the sick_perception_sdk (`sick::version()`)
- Does not connect to a device
- Expected device configuration: None

## Configuration

This example [shared/configuration.cpp](shared/configuration.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints the following information from the connected device: device type, firmware version, location name, order number, serial number, system time, device IP address, and operating hours
- Sets the echo filter to `FirstEcho`
- Enables Compact measurement data streaming:
  - picoScan100, multiScan100: UDP to IP address `192.168.0.100`, port `2115` (configurable with `--receiver_address` and `--receiver_port`)
  - LRS4000, multiScan200: TCP, the device provides the data on port `2115`
- Expected device configuration: Factory defaults, licenses for used functions available

## Data streaming UDP (picoScan100, multiScan100)

This example [shared/data_streaming_udp.cpp](shared/data_streaming_udp.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Enables IMU data streaming (UDP) to IP address `192.168.0.100`, port `7503`
- Enables encoder data streaming (UDP) to IP address `192.168.0.100`, port `7504`
- Receives and prints metadata for frame point cloud data, IMU data, and encoder data
- Expected device configuration: Factory defaults, licenses for used functions available

## Data streaming UDP multicast (picoScan100, multiScan100)

This example [shared/data_streaming_udp_multicast.cpp](shared/data_streaming_udp_multicast.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Enables measurement data streaming (UDP) to multicast group address `239.255.0.1`, port `2115`
- Enables IMU data streaming (UDP) to multicast group address `239.255.0.1`, port `7503`
- Enables encoder data streaming (UDP) to multicast group address `239.255.0.1`, port `7504`
- Joins the multicast group on the local network interface for each receiver before starting to receive data
- Receives and prints metadata for frame point cloud data, IMU data, and encoder data
- Expected device configuration: Factory defaults, licenses for used functions available, network switch between device and computer with IGMP snooping enabled

## Data streaming TCP (LRS4000, multiScan200)

This example [shared/data_streaming_tcp.cpp](shared/data_streaming_tcp.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Sets the measurement data format to Compact
- Receives and prints metadata for frame point cloud data
- Expected device configuration: Factory defaults, licenses for used functions available

## Low-level streaming UDP (picoScan100, multiScan100)

This example [shared/low_level_streaming_udp.cpp](shared/low_level_streaming_udp.cpp)

- Listens for UDP packets on port `2115` (format Compact)
- Receives raw data from the socket using a reusable buffer
- Parses and validates Compact telegrams from the received data
- Prints the number of modules in each received scan data frame
- Demonstrates low-level handling of UDP streaming data without using high-level device configuration APIs
- Expected device configuration: Device streaming Compact data on UDP port 2115

## Low-level streaming TCP (LRS4000, multiScan200)

This example [shared/low_level_streaming_tcp.cpp](shared/low_level_streaming_tcp.cpp)

- Establishes a TCP connection to the device using the specified IP address or the default IP address (192.168.0.1 if no IP is specified) on port `2115`
- Receives raw data from the socket using a reusable buffer
- Extracts Compact telegrams from the received data stream using StreamExtractor
- Parses and validates the scan data telegrams
- Prints the number of modules in each received scan data frame
- Demonstrates low-level handling of TCP streaming data without using high-level device configuration APIs
- Expected device configuration: Device streaming Compact data on TCP port 2115

## Multiple devices (picoScan100, multiScan100)

This example [shared/data_streaming_udp_multiple_devices.cpp](shared/data_streaming_udp_multiple_devices.cpp)

- Establishes connections to two devices: the first one at the specified IP address (default 192.168.0.1), the second one at the IP address given with `--sensor_address_2` (default 192.168.0.2)
- Reads and prints the IP addresses of both devices
- Enables Compact measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115` for the first device and port `2116` for the second device
- Receives the frame point clouds of both devices for 10 seconds and prints the number of points per frame
- Expected device configuration: Factory defaults with different IP addresses, licenses for used functions available

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

This example [shared/data_streaming_udp_segmented_data.cpp](shared/data_streaming_udp_segmented_data.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Enables Compact measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Receives the scan data segments individually, without combining them into frames, for 10 seconds
- Prints the telegram sequence number and the number of layers of each module for every segment
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

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Requires the new IP address with `--new_address`, for example `--new_address 192.168.0.50`. Use an unused address in the same subnet as the computer.
- Configures new static IP settings (IP address: value of `--new_address`, subnet mask: 255.255.255.0, gateway: 0.0.0.0), then reads them back and prints them
- Applies the IP configuration changes and waits until the device is reachable at the new address
- Reconnects to the device using the new IP address and prints it
- Changes the IP address back to the original address in the same way, so the device stays available for the other examples
- Expected device configuration: Factory defaults

## Download and import configuration (picoScan100, multiScan100, multiScan200)

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

## Firmware update (picoScan100, multiScan100, multiScan200)

This example [shared/firmware_update.cpp](shared/firmware_update.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Requires the path to the firmware file with `-f` or `--file` (`*.spk.signed` for picoScan100 and multiScan100, `*.swp` for multiScan200)
- Reads and prints the device type and the firmware version before the update
- Reads the power-on counter to detect the restart after the update
- Uploads and installs the firmware with a timeout of 5 minutes. Do not power off the device during the update.
- Waits up to 1 minute until the device has restarted. Log messages `Could not establish connection` during the restart are expected.
- Reads and prints the firmware version after the update
- Expected device configuration: Firmware file that matches the device type

## More device configuration

All configuration and status interactions with the sensor are based on the sensors REST APIs. A summary of all available sensor configuration via the SDK can be found here [doc/device_configuration_overview.md](../doc/device_configuration_overview.md).
