/*
 * libopensync - A synchronization framework
 * Copyright (C) 2006  NetNix Finland Ltd <netnix@netnix.fi>
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
 * Author: Daniel Friedrich <daniel.friedrich@opensync.org>
 * 
 */
 
#ifndef OPENSYNC_VERSION_H_
#define OPENSYNC_VERSION_H_

#include <opensync/opensync_list.h>

OSYNC_EXPORT OSyncVersion *osync_version_new(OSyncError **error);
OSYNC_EXPORT OSyncVersion *osync_version_ref(OSyncVersion *version);
OSYNC_EXPORT void osync_version_unref(OSyncVersion *version);

OSYNC_EXPORT void osync_version_set_plugin(OSyncVersion *version, const char *plugin);
OSYNC_EXPORT void osync_version_set_priority(OSyncVersion *version, const char *priority);
OSYNC_EXPORT void osync_version_set_vendor(OSyncVersion *version, const char *vendor);
OSYNC_EXPORT void osync_version_set_modelversion(OSyncVersion *version, const char *modelversion);
OSYNC_EXPORT void osync_version_set_firmwareversion(OSyncVersion *version, const char *firmwareversion);
OSYNC_EXPORT void osync_version_set_softwareversion(OSyncVersion *version, const char *softwareversion);
OSYNC_EXPORT void osync_version_set_hardwareversion(OSyncVersion *version, const char *hardwareversion);
OSYNC_EXPORT void osync_version_set_identifier(OSyncVersion *version, const char *identifier);

#endif /*OPENSYNC_VERSION_H_*/
