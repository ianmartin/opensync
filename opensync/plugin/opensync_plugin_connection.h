/*
 * libopensync - A synchronization framework
 * Copyright (C) 2008  Daniel Gollub <dgollub@suse.de>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

#ifndef _OPENSYNC_PLUGIN_CONNECTION_H_
#define _OPENSYNC_PLUGIN_CONNECTION_H_

/**
 * @defgroup OSyncPluginConnectionAPI OpenSync Plugin Connection Options
 * @ingroup OSyncPublic
 * @brief Functions to get and set a plugin's connection options
 *
 */

/*@{*/

/*! @brief Connection type support flags
 *
 **/
typedef enum {
  /** Unknown */
  OSYNC_PLUGIN_CONNECTION_UNKNOWN	= 0,
  /** Bluetooth */
  OSYNC_PLUGIN_CONNECTION_BLUETOOTH	= (1 << 0),
  /** USB */
  OSYNC_PLUGIN_CONNECTION_USB		= (1 << 1),
  /** Network */ 
  OSYNC_PLUGIN_CONNECTION_NETWORK	= (1 << 2), 
  /** Serial */
  OSYNC_PLUGIN_CONNECTION_SERIAL	= (1 << 3),
  /** IrDA */
  OSYNC_PLUGIN_CONNECTION_IRDA		= (1 << 4)
} OSyncPluginConnectionType;

/*! @brief Connection type
 * 
 */
typedef OSyncPluginConnectionType OSyncPluginConnectionSupportedFlag;

/*! @brief Set of OSyncPluginConnectionType values
 * 
 */
typedef unsigned int OSyncPluginConnectionSupportedFlags;

/*! @brief Connection option support flags
 * 
 */
typedef enum {
  /** Bluetooth (MAC) address */
  OSYNC_PLUGIN_CONNECTION_BLUETOOTH_ADDRESS	= (1 << 0),
  /** Bluetooth RFCOMM channel */
  OSYNC_PLUGIN_CONNECTION_BLUETOOTH_RFCOMM	= (1 << 1),
  /** Bluetooth SDP UUID */
  OSYNC_PLUGIN_CONNECTION_BLUETOOTH_SDPUUID	= (1 << 2),
  /** USB Vendor ID */
  OSYNC_PLUGIN_CONNECTION_USB_VENDORID		= (1 << 3),
  /** USB Product ID */
  OSYNC_PLUGIN_CONNECTION_USB_PRODUCTID		= (1 << 4),
  /** USB interface ??? */
  OSYNC_PLUGIN_CONNECTION_USB_INTERFACE		= (1 << 5),
  /** Network address (IP/hostname) */
  OSYNC_PLUGIN_CONNECTION_NETWORK_ADDRESS	= (1 << 6),
  /** Network port */
  OSYNC_PLUGIN_CONNECTION_NETWORK_PORT		= (1 << 7),
  /** Network protocol */
  OSYNC_PLUGIN_CONNECTION_NETWORK_PROTOCOL	= (1 << 8),
  /** Network DNS-SD service type */
  OSYNC_PLUGIN_CONNECTION_NETWORK_DNSSD		= (1 << 9),
  /** Serial port speed (bps) eg. 115200 */
  OSYNC_PLUGIN_CONNECTION_SERIAL_SPEED		= (1 << 10),
  /** Serial device node (e.g. /dev/ttyS0, /dev/ttyUSB0, ...) */
  OSYNC_PLUGIN_CONNECTION_SERIAL_DEVICENODE	= (1 << 11),
  /** IrDA Identifier (Service) String */
  OSYNC_PLUGIN_CONNECTION_IRDA_SERVICE		= (1 << 12)
} OSyncPluginConnectionOptionSupportedFlag;

/*! @brief Set of OSyncPluginConnectionOptionSupportedFlag values
 * 
 */
typedef unsigned int OSyncPluginConnectionOptionSupportedFlags;

/*! @brief Create a new OSyncPluginConnection object
 *
 * @param error Pointer to an error struct
 * @returns the newly created object, or NULL in case of an error.
 *
 */
OSYNC_EXPORT OSyncPluginConnection *osync_plugin_connection_new(OSyncError **error);

/*! @brief Decrease the reference count on an OSyncPluginConnection object
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_unref(OSyncPluginConnection *connection);

/*! @brief Increase the reference count on an OSyncPluginConnection object
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The OSyncPluginConnection object passed in
 * 
 */
OSYNC_EXPORT OSyncPluginConnection *osync_plugin_connection_ref(OSyncPluginConnection *connection);


/*! @brief Get the type of a connection
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The connection type
 * 
 */
OSYNC_EXPORT OSyncPluginConnectionType osync_plugin_connection_get_type(OSyncPluginConnection *connection);

/*! @brief Set the type of a connection
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param type The connection type to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_set_type(OSyncPluginConnection *connection, OSyncPluginConnectionType type);


/*! @brief Check if a type of connection is supported
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param flag The connection type to check
 * @returns true if the connection type is supported, false otherwise.
 * 
 */
OSYNC_EXPORT osync_bool osync_plugin_connection_is_supported(OSyncPluginConnection *connection, OSyncPluginConnectionSupportedFlag flag);

/*! @brief Set the types of a connection that are supported
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param flags The set of connection types to set as supported
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_set_supported(OSyncPluginConnection *connection, OSyncPluginConnectionSupportedFlags flags);


/*! @brief Check if a connection option is supported
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param flag The connection option to check
 * @returns true if the connection option is supported, false otherwise.
 * 
 */
OSYNC_EXPORT osync_bool osync_plugin_connection_option_is_supported(OSyncPluginConnection *connection, OSyncPluginConnectionOptionSupportedFlag flag);

/*! @brief Set the connection options that are supported
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param flags The set of connection options to set as supported
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_option_set_supported(OSyncPluginConnection *connection, OSyncPluginConnectionOptionSupportedFlags flags);


/* Bluetooth */

/*! @brief Get the Bluetooth address
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The bluetooth address or NULL if not set
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_bt_get_addr(OSyncPluginConnection *connection);


/*! @brief Set the Bluetooth address
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param address The bluetooth address to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_bt_set_addr(OSyncPluginConnection *connection, const char *address);

/*! @brief Get the Bluetooth RFCOMM channel
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The RFCOMM channel
 * 
 */
OSYNC_EXPORT unsigned int osync_plugin_connection_bt_get_channel(OSyncPluginConnection *connection);

/*! @brief Set the Bluetooth RFCOMM channel
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param channel The RFCOMM channel to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_bt_set_channel(OSyncPluginConnection *connection, unsigned int channel);


/*! @brief Get the Bluetooth SDP UUID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The SDP UUID or NULL if not set
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_bt_get_sdpuuid(OSyncPluginConnection *connection);

/*! @brief Set the Bluetooth SDP UUID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param sdpuuid The SDP UUID to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_bt_set_sdpuuid(OSyncPluginConnection *connection, const char *sdpuuid);

/* USB */

/*! @brief Get the USB vendor ID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The USB vendor ID
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_usb_get_vendorid(OSyncPluginConnection *connection);

/*! @brief Set the USB vendor ID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param vendorid The USB vendor ID to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_usb_set_vendorid(OSyncPluginConnection *connection, const char *vendorid);


/*! @brief Get the USB product ID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The USB product ID
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_usb_get_productid(OSyncPluginConnection *connection);

/*! @brief Set the USB product ID
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param productid The USB product ID to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_usb_set_productid(OSyncPluginConnection *connection, const char *productid);


/*! @brief Get the USB interface number
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The USB interface number
 * 
 */
OSYNC_EXPORT unsigned int osync_plugin_connection_usb_get_interface(OSyncPluginConnection *connection);

/*! @brief Set the USB interface number
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param interf The USB interface number to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_usb_set_interface(OSyncPluginConnection *connection, unsigned int interf);


/* Network */

/*! @brief Get the network address (IP address or hostname)
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The network address
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_net_get_address(OSyncPluginConnection *connection);

/*! @brief Set the network address (IP address or hostname)
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param address The network address to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_net_set_address(OSyncPluginConnection *connection, const char *address);


/*! @brief Get the network port
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The network port
 * 
 */
OSYNC_EXPORT unsigned int osync_plugin_connection_net_get_port(OSyncPluginConnection *connection);

/*! @brief Set the network port
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param port The network port to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_net_set_port(OSyncPluginConnection *connection, unsigned int port);


/*! @brief Get the network protocol
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The network protocol
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_net_get_protocol(OSyncPluginConnection *connection);

/*! @brief Set the network protocol
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param protocol The network protocol to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_net_set_protocol(OSyncPluginConnection *connection, const char *protocol);


/*! @brief Get the network DNS-SD service type
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The DNS-SD service type or NULL if not set
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_net_get_dnssd(OSyncPluginConnection *connection);

/*! @brief Set the network DNS-SD service type
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param dnssd The DNS-SD service type to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_net_set_dnssd(OSyncPluginConnection *connection, const char *dnssd);


/* Serial */

/*! @brief Get the serial port speed
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The serial port speed, in bps
 * 
 */
OSYNC_EXPORT unsigned int osync_plugin_connection_serial_get_speed(OSyncPluginConnection *connection);

/*! @brief Set the serial port speed
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param speed The serial port speed to set, in bps
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_serial_set_speed(OSyncPluginConnection *connection, unsigned int speed);


/*! @brief Get the serial port device
 * 
 * The serial port device node, eg. /dev/ttyS0, /dev/ttyUSB0 etc.
 *
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The serial port device node
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_serial_get_devicenode(OSyncPluginConnection *connection);

/*! @brief Set the serial port device
 * 
 * The serial port device node, eg. /dev/ttyS0, /dev/ttyUSB0 etc.
 *
 * @param connection Pointer to the OSyncPluginConnection object
 * @param devicenode The serial port device node to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_serial_set_devicenode(OSyncPluginConnection *connection, const char *devicenode);


/* IrDA */

/*! @brief Get the IrDA identifier (service) string
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @returns The IrDA service string
 * 
 */
OSYNC_EXPORT const char *osync_plugin_connection_irda_get_service(OSyncPluginConnection *connection);

/*! @brief Set the IrDA identifier (service) string
 * 
 * @param connection Pointer to the OSyncPluginConnection object
 * @param irdaservice The IrDA service string to set
 * 
 */
OSYNC_EXPORT void osync_plugin_connection_irda_set_service(OSyncPluginConnection *connection, const char *irdaservice);

/*@}*/

#endif /*_OPENSYNC_PLUGIN_CONNECTION_H_*/

