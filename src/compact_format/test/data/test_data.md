# Compact Format Test Data

This folder contains file with raw data for the supported Compact streaming formats.

| file name                                                      | description                                                                                                                                                                                                 |
| -------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `telegram_type_1_LRS4581-frame<i>.bin`                         | Type 1 (scan data) data recorded from an LRS4581 device.                                                                                                                                                    |
| `telegram_type_1_multiScan136-frame<i>.bin`                    | Type 1 (scan data) data from a multiScan136 device.                                                                                                                                                         |
| `telegram_type_1_picoScan150_profile_1-frame<i>.bin`           | Type 1 (scan data) data from a picoScan150 device with scan profile 1.                                                                                                                                      |
| `telegram_type_2_multiScan136-frame<i>.bin`                    | Type 2 (IMU) data from a multiScan136.                                                                                                                                                                      |
| `telegram_type_2_multiScan270-frame<i>.bin`                    | Type 2 (IMU) data from a multiScan270.                                                                                                                                                                      |
| `telegram_type_3_multiScan270_profile_12-frame<i>.bin`         | Type 3 (ambient light) data from a multiScan270 with profile 12.                                                                                                                                            |
| `telegram_type_4_v1_picoScan150-frame<i>.bin`                  | Type 4 version 1 (encoder) data from a picoScan150.                                                                                                                                                         |
| `telegram_type_6_multiScan270_profile_12_minimal-frame<i>.bin` | Type 6 (multiScan200) data from a multiScan270 with all optional fields disabled and only first echo. Scans contain reflector, blooming and particle points (but no properties, so points are not flagged). |
| `telegram_type_6_multiScan270_profile_12_full-frame<i>.bin`    | Type 6 (multiScan200) data from a multiScan270 with all fields (intensity, ambient light, properties) and all echoes enabled. Scans contain reflector, blooming and particle points.                        |
| `telegram_type_7_multiScan270-frame<i>.bin`                   | Type 7 (IMU) data from a multiScan270.                                                                                                                                                                      |

`<i>` = 0, 1, 2 is a placeholder for the frame index to represent consecutive frames from the same recording.
