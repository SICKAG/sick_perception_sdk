# multiScan200 Learning Examples

- [Diagnosis](#diagnosis)
- [Write to PCD files](#write-to-pcd-files)
- [More device configuration](#more-device-configuration)

## Diagnosis

This example [multiScan200/diagnosis.cpp](multiScan200/diagnosis.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints device information: IP address, link to the diagnosis overview in the web UI, device type, firmware version, location name, order number, serial number, and system time
- Calls find-me function; the device LEDs blink for 5 seconds
- Sets the data output mode to Compact over TCP
- Receives measurement data via TCP from the device on port `2115` and prints the telegram sequence number of every 100th frame
- Monitors and reports lost data (telegrams, frames, and segments). If the interval filter is enabled, its reduction factor is taken into account.
- Continuously monitors and prints device state, temperature, and contamination data every 2 seconds
- Runs until you stop it with Ctrl+C
- Expected device configuration: Factory defaults, licenses for used functions available

## Write to PCD files

This example [multiScan200/write_to_pcd_bmp_files.cpp](multiScan200/write_to_pcd_bmp_files.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Configures streaming mode to Compact format
- Creates a new PCD file with the latest point cloud every time a new frame is received
- Creates a new BMP file with the latest ambient light data every time a new frame is received
- PCD files are written to a `multiScan200_files` directory in the current working directory
- Expected device configuration: Factory defaults, licenses for used functions available

## More device configuration

All configuration and status interactions with the sensor are based on the sensors REST APIs. A summary of all available sensor configuration via the SDK can be found here [doc/device_configuration_overview.md](../doc/device_configuration_overview.md).
