/*
 * xmlformat-event - A plugin for parsing vevent objects for the opensync framework
 * Copyright (C) 2004-2005  Armin Bauer <armin.bauer@opensync.org>
 * Copyright (C) 2007  Daniel Gollub <dgollub@suse.de>
 * Copyright (C) 2007  Christopher Stender <cstender@suse.de>
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

#ifndef XMLFORMAT_EVENT_H_
#define XMLFORMAT_EVENT_H_

#include <opensync/opensync.h>
#include <opensync/opensync-merger.h>
#include <opensync/opensync-serializer.h>
#include <opensync/opensync-format.h>
#include <opensync/opensync-time.h>

#include "vformat.h"
#include "xmlformat.h"
#include "xmlformat-vcal.h"
#include "xmlformat-ical.h"

OSyncConvCmpResult compare_event(const char *leftdata, unsigned int leftsize, const char *rightdata, unsigned int rightsize);
void create_event(char **data, unsigned int *size);
time_t get_revision(const char *data, unsigned int size, OSyncError **error);

#endif //XMLFORMAT_EVENT_H_