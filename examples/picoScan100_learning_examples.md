# picoScan100 Learning Examples

- [Diagnosis](#diagnosis)
- [More device configuration](#more-device-configuration)

## Diagnosis

This example [picoScan100/diagnosis.cpp](picoScan100/diagnosis.cpp)

- Establishes a connection to the device using the specified IP address (CMD interface) or the default IP address (192.168.0.1 if no IP is specified)
- Reads and prints device information: device type, device state, firmware version, location name, order number, serial number, and system time
- Calls find-me function; the device LEDs blink for 5 seconds
- Starts measurement
- Enables measurement data streaming (UDP) to IP address `192.168.0.100`, port `2115`
- Continuously monitors and prints device state, temperature, and contamination data every 5 seconds
- Monitors and reports lost data (telegrams, frames, and segments)
- Expected device configuration: Factory defaults, licenses for used functions available

## More device configuration

All configuration and status interactions with the sensor are based on the sensors REST APIs. A summary of all available sensor configuration via the SDK can be found here [doc/device_configuration_overview.md](../doc/device_configuration_overview.md).
