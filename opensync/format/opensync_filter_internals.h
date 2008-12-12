/*
 * libopensync - A synchronization framework
 * Copyright (C) 2004-2005  Armin Bauer <armin.bauer@opensync.org>
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

#ifndef _OPENSYNC_FILTER_INTERNALS_H_
#define _OPENSYNC_FILTER_INTERNALS_H_

/**
 * @defgroup OSyncFilterInternalAPI OpenSync Filter Internals
 * @ingroup OSyncFormatPrivate
 * @brief OpenSync format filters internal API
 **/

/*@{*/

/** @brief The action that should be invoked */
typedef enum OSyncFilterAction {
	/** This filter should be ignored */
	OSYNC_FILTER_IGNORE = 0,
	/** The change should be allowed to pass (overrides previous action) */
	OSYNC_FILTER_ALLOW = 1,
	/** The change should be prevented from passing (overrides previous action) */
	OSYNC_FILTER_DENY = 2
} OSyncFilterAction;

typedef osync_bool (* OSyncFilterFunction) (OSyncData *data, const char *config);

/** @brief Creates a new filter
 * 
 * @param objtype the object type handled by the filter
 * @param action the action that should be invoked by the filter
 * @param error Pointer to an error struct
 * @returns A newly allocated filter
 **/
OSYNC_TEST_EXPORT OSyncFilter *osync_filter_new(const char *objtype, OSyncFilterAction action, OSyncError **error);

/** @brief Creates a new filter that uses a custom filter
 * 
 * @param custom_filter Custom filter to use
 * @param config configuration to be used by the custom filter. Must be a null-terminated string.
 * @param action the action that should be invoked by the filter
 * @param error Pointer to an error struct
 * @returns A newly allocated filter
 **/
OSYNC_TEST_EXPORT OSyncFilter *osync_filter_new_custom(OSyncCustomFilter *custom_filter, const char *config, OSyncFilterAction action, OSyncError **error);

/** @brief Increase the reference count on a filter
 * 
 * @param filter Pointer to the filter
 * 
 */
OSyncFilter *osync_filter_ref(OSyncFilter *filter);

/** @brief Decrease the reference count on a filter
 * 
 * @param filter Pointer to the filter
 * 
 */
OSYNC_TEST_EXPORT void osync_filter_unref(OSyncFilter *filter);

/** @brief Sets the config for a filter
 * 
 * Config must be a null-terminated string
 * 
 * @param filter The filter
 * @param config The new config for this filter
 **/
OSYNC_TEST_EXPORT void osync_filter_set_config(OSyncFilter *filter, const char *config);

/** @brief Gets the config of a filter
 * 
 * @param filter The filter
 * @returns The config of this filter
 **/
OSYNC_TEST_EXPORT const char *osync_filter_get_config(OSyncFilter *filter);

/** @brief Gets the object type of a filter
 * 
 * @param filter The filter
 * @returns The object type handled by the specified filter
 **/
OSYNC_TEST_EXPORT const char *osync_filter_get_objtype(OSyncFilter *filter);

/** @brief Invokes a filter on a data object
 * 
 * @param filter The filter
 * @param data The data to be passed into the filter
 * @returns The result of the filter (action)
 **/
OSyncFilterAction osync_filter_invoke(OSyncFilter *filter, OSyncData *data);

/** @brief Creates a new custom filter
 * 
 * @param objtype the object type handled by the custom filter
 * @param objformat the object format handled by the custom filter
 * @param name name of the custom filter
 * @param hook the filter callback function
 * @param error Pointer to an error struct
 * @returns A newly allocated custom filter
 **/
OSYNC_TEST_EXPORT OSyncCustomFilter *osync_custom_filter_new(const char *objtype, const char *objformat, const char *name, OSyncFilterFunction hook, OSyncError **error);

/** @brief Increase the reference count on a custom filter
 * 
 * @param filter Pointer to the custom filter
 * 
 */
OSyncCustomFilter *osync_custom_filter_ref(OSyncCustomFilter *filter);

/** @brief Decrease the reference count on a custom filter
 * 
 * @param filter Pointer to the custom filter
 * 
 */
OSYNC_TEST_EXPORT void osync_custom_filter_unref(OSyncCustomFilter *filter);

/** @brief Invokes a custom filter on a data object
 * 
 * @param filter The custom filter
 * @param data The data to be passed into the custom filter
 * @param config Configuration to be used by the custom filter. Must be a null-terminated string.
 * @returns The result of the filter (action)
 **/
osync_bool osync_custom_filter_invoke(OSyncCustomFilter *filter, OSyncData *data, const char *config);

/*@}*/

#endif /* _OPENSYNC_FILTER_INTERNALS_H_ */

