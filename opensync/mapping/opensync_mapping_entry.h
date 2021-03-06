/*
 * libopensync - A synchronization framework
 * Copyright (C) 2004-2006  Armin Bauer <armin.bauer@desscon.com>
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
 
#ifndef OPENSYNC_MAPPING_ENTRY_H_
#define OPENSYNC_MAPPING_ENTRY_H_

OSYNC_EXPORT OSyncMappingEntry *osync_mapping_entry_new(OSyncError **error);
OSYNC_EXPORT OSyncMappingEntry *osync_mapping_entry_ref(OSyncMappingEntry *entry);
OSYNC_EXPORT void osync_mapping_entry_unref(OSyncMappingEntry *entry);

OSYNC_EXPORT osync_bool osync_mapping_entry_matches(OSyncMappingEntry *entry, OSyncChange *change);

/*
OSYNC_EXPORT void osync_mapping_entry_update(OSyncMappingEntry *entry, OSyncChange *change);
OSYNC_EXPORT OSyncChange *osync_mapping_entry_get_change(OSyncMappingEntry *entry);

OSYNC_EXPORT osync_bool osync_mapping_entry_is_dirty(OSyncMappingEntry *entry);
OSYNC_EXPORT void osync_mapping_entry_set_dirty(OSyncMappingEntry *entry, osync_bool dirty);
 */

OSYNC_EXPORT void osync_mapping_entry_set_uid(OSyncMappingEntry *entry, const char *uid);
OSYNC_EXPORT const char *osync_mapping_entry_get_uid(OSyncMappingEntry *entry);

OSYNC_EXPORT long long int osync_mapping_entry_get_member_id(OSyncMappingEntry *entry);
OSYNC_EXPORT void osync_mapping_entry_set_member_id(OSyncMappingEntry *entry, long long int id);

OSYNC_EXPORT long long int osync_mapping_entry_get_id(OSyncMappingEntry *entry);
OSYNC_EXPORT void osync_mapping_entry_set_id(OSyncMappingEntry *entry, long long int id);

#endif /*OPENSYNC_MAPPING_ENTRY_H_*/
