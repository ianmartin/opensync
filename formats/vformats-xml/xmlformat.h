/*
 * xmlformat - Common code base for xmlformat-* plugins. 
 * Copyright (C) 2004-2005  Armin Bauer <armin.bauer@opensync.org>
 * Copyright (C) 2006  Daniel Friedrich <daniel.friedrich@opensync.org>
 * Copyright (C) 2007  Daniel Gollub <dgollub@suse.de>
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

#ifndef XMLFORMAT_H_
#define XMLFORMAT_H_

#include <stdio.h>
#include <string.h>

#include <opensync/opensync.h>
#include <opensync/opensync-merger.h>
#include <opensync/opensync-serializer.h>
#include <opensync/opensync-format.h>
#include <opensync/opensync-time.h>

#include "vformat.h"

#define HANDLE_IGNORE (void *)1

typedef struct OSyncHookTables {
	GHashTable *attributes;
	GHashTable *parameters;
} OSyncHookTables;

/*** PARAMETER ***/
void handle_value_parameter(OSyncXMLField *xmlfield, VFormatParam *param);

OSyncXMLField *handle_attribute_simple_content(OSyncXMLFormat *xmlformat, VFormatAttribute *attr, const char *name, OSyncError **error); 
OSyncXMLField *handle_categories_attribute(OSyncXMLFormat *xmlformat, VFormatAttribute *attr, OSyncError **error);
OSyncXMLField *handle_class_attribute(OSyncXMLFormat *xmlformat, VFormatAttribute *attr, OSyncError **error);
OSyncXMLField *handle_uid_attribute(OSyncXMLFormat *xmlformat, VFormatAttribute *attr, OSyncError **error); 
OSyncXMLField *handle_url_attribute(OSyncXMLFormat *xmlformat, VFormatAttribute *attr, OSyncError **error); 

osync_bool needs_encoding(const unsigned char *tmp, const char *encoding);
osync_bool needs_charset(const unsigned char *tmp);

void add_value(VFormatAttribute *attr, OSyncXMLField *xmlfield, const char *name, const char *encoding);
void add_values(VFormatAttribute *attr, OSyncXMLField *xmlfield, const char *encoding);
void add_values_from_nth_field_on(VFormatAttribute *attr, OSyncXMLField *xmlfield, const char *encoding, int nth);

void destroy_xmlformat(char *input, size_t inpsize);
osync_bool copy_xmlformat(const char *input, unsigned int inpsize, char **output, unsigned int *outpsize, OSyncError **error);
char *print_xmlformat(const char *data, unsigned int size);

osync_bool marshal_xmlformat(const char *input, unsigned int inpsize, OSyncMessage *message, OSyncError **error);
osync_bool demarshal_xmlformat(OSyncMessage *message, char **output, unsigned int *outpsize, OSyncError **error);


/* VFormat Handler for Attributes and Parameters */
void handle_parameter(OSyncHookTables *hooks, OSyncXMLField *xmlfield, VFormatParam *param);
void handle_attribute(OSyncHookTables *hooks, OSyncXMLFormat *xmlformat, VFormatAttribute *attr, OSyncError **error);

/* XML Handler for Attributes and Parameters */
void xml_handle_parameter(OSyncHookTables *hooks, VFormatAttribute *attr, OSyncXMLField *xmlfield, int attr_nr);
void xml_handle_attribute(OSyncHookTables *hooks, VFormat *vcard, OSyncXMLField *xmlfield, const char *encoding);

#endif // XMLFORMAT_H_

