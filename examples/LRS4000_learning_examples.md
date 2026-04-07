# LRS4000 Examples

- [Diagnosis](#diagnosis)
- [Write to PCD files](#write-to-pcd-files)
- [More device configuration](#more-device-configuration)

## Diagnosis

This example [LRS4000/diagnosis.cpp](LRS4000/diagnosis.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints device information: device type, device state, firmware version, location name, order number, serial number, and system time
- Calls find-me function; the device LEDs blink for 5 seconds
- Starts measurement
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Continuously monitors and prints device state, temperature, and contamination data every 5 seconds
- Monitors and reports lost data (telegrams, frames, and segments)
- Expected device configuration: Factory defaults, licenses for used functions available

## Write to PCD files

This example [LRS4000/write_to_pcd_files.cpp](LRS4000/write_to_pcd_files.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Configures streaming mode to Compact format
- Creates a new PCD file with the latest point cloud every time a new frame is received
- PCD files are written to a `pcd_files` directory in the current working directory
- Expected device configuration: Factory defaults, licenses for used functions available

## More device configuration

All configuration and status interactions with the sensor are based on the sensors REST APIs. A summary of all available sensor configuration via the SDK can be found here [doc/device_configuration_overview.md](../doc/device_configuration_overview.md).
