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

#ifndef _OPENSYNC_MODULE_H_
#define _OPENSYNC_MODULE_H_

OPENSYNC_BEGIN_DECLS

OSYNC_EXPORT OSyncModule *osync_module_new(OSyncError **error);
OSYNC_EXPORT void osync_module_free(OSyncModule *module);

OSYNC_EXPORT osync_bool osync_module_load(OSyncModule *module, const char *path, OSyncError **error);
OSYNC_EXPORT void osync_module_unload(OSyncModule *module);

OSYNC_EXPORT osync_bool osync_module_get_sync_info(OSyncModule *module, OSyncPluginEnv *env, OSyncError **error);
OSYNC_EXPORT osync_bool osync_module_get_format_info(OSyncModule *module, OSyncFormatEnv *env, OSyncError **error);
OSYNC_EXPORT osync_bool osync_module_get_conversion_info(OSyncModule *module, OSyncFormatEnv *env, OSyncError **error);

OSYNC_EXPORT int osync_module_get_version(OSyncModule *module);
OSYNC_EXPORT osync_bool osync_module_check(OSyncModule *module, OSyncError **error);

OSYNC_EXPORT void *osync_module_get_function(OSyncModule *module, const char *name, OSyncError **error);

OPENSYNC_END_DECLS

#endif //_OPENSYNC_MODULE_H_
