/*
 * libopensync - A synchronization framework
 * Copyright (C) 2008       Daniel Gollub <dgollub@suse.de>
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

#ifndef _OPENSYNC_OBJFORMAT_SINK_H_
#define _OPENSYNC_OBJFORMAT_SINK_H_

/**
 * @defgroup OSyncObjFormatSinkAPI OpenSync Object Format Sink
 * @ingroup OSyncFormat
 * @brief Functions for handling object formats sinks
 * 
 */
/*@{*/

/**
 * @brief Creates a new object format sink
 * @param objformat the objformat 
 * @param error Pointer to an error struct
 * @return The pointer to the newly allocated object format sink or NULL in case of error
 */
OSYNC_EXPORT OSyncObjFormatSink *osync_objformat_sink_new(const char *objformat, OSyncError **error);

/** @brief Increase the reference count on an object format
 * 
 * @param format Pointer to the object format
 * 
 */
OSYNC_EXPORT OSyncObjFormatSink *osync_objformat_sink_ref(OSyncObjFormatSink *format);

/** @brief Decrease the reference count on an object format
 * 
 * @param format Pointer to the object format
 * 
 */
OSYNC_EXPORT void osync_objformat_sink_unref(OSyncObjFormatSink *format);

/**
 * @brief Returns the objformat of the sink 
 * @param format Pointer to the object format sink
 * @return Pointer to object format name
 */
OSYNC_EXPORT const char *osync_objformat_sink_get_objformat(OSyncObjFormatSink *format);

/**
 * @brief Returns the conversion path config of an object format sink
 * @param format Pointer to the object format
 * @return The conversion config of the specified object format's object type
 */
OSYNC_EXPORT const char *osync_objformat_sink_get_config(OSyncObjFormatSink *format);

/**
 * @brief Set the conversion path config of an object format sink
 * @param format Pointer to the object format sink
 * @param config Format specific configuration 
 * @return The conversion config of the specified object format sink
 */
OSYNC_EXPORT void osync_objformat_sink_set_config(OSyncObjFormatSink *format, const char *format_config);

/*@}*/

#endif //_OPENSYNC_OBJFORMAT_SINK_H_
