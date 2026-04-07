/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @defgroup Drivers Drivers
 * @brief High-level interface for receiving sensor data streams.
 *
 * The drivers classes provide a unified interface for receiving and processing data from
 * SICK sensors. Each driver runs its data streams in dedicated threads without internal queuing.
 *
 * ## Data Streams
 *
 * Each sensor provides data through multiple independent streams (e.g. scan data, IMU, encoder data).
 * Streams can be enabled or disabled independently.
 *
 * ## Callbacks
 *
 * Each stream offers one or more callbacks. When multiple callbacks exist for a stream,
 * they differ in:
 * - **data type**: e.g., raw scan data vs. point cloud,
 * - **data segmentation**: e.g., individual segments vs. complete frames.
 *
 * ### Frames and Segments
 *
 * A **frame** represents sensor data covering the full field of view once:
 * - For rotating LiDAR sensors one frame contains the data measured during one full revolution.
 * - For a camera or other solid state devices one frame contains one captured image.
 *
 * A **segment** is a portion of a frame.
 *
 * ## Connection Types
 *
 * Sensors use different connection protocols:
 * - **TCP devices** (e.g., LRS4000): Use `sensorPort` to specify the port
 *   on the device to which to connect.
 * - **UDP devices** (e.g., picoScan100, multiScan100): Use `receiverPort` to specify the
 *   port on which to listen for incoming UDP packets. Listens on all interfaces.
 *
 * ## Receiver Timeouts
 *
 * When setting up a data receiver, two timeout parameters control error detection:
 * - **firstDataTimeout**: If more time has passed than specified since the stream was started
 *   without receiving any data, an exception is raised. A value of 0 means no timeout.
 * - **newDataTimeout**: If more time has passed than specified without receiving any data after
 *   the first data was received, an exception is raised. A value of 0 means no timeout.
 *
 * ## Performance Considerations
 *
 * - **Callbacks must be lightweight**: Processing time should be shorter than the data
 *   cycle time to avoid blocking the receiver thread too long thus losing data.
 * - **Enabling a stream** incurs the cost of converting the wire protocol to SDK data
 *   structures, even without registered callbacks.
 * - **Registering callbacks** may incur additional conversion costs in the driver (e.g., building
 *   point clouds or assembling segments into frames).
 */
