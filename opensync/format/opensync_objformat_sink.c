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
 
#include "opensync.h"
#include "opensync_internals.h"

#include "opensync-format.h"
#include "opensync_objformat_sink_private.h"

OSyncObjFormatSink *osync_objformat_sink_new(const char *objformat, OSyncError **error)
{
  OSyncObjFormatSink *formatsink = NULL;
  osync_trace(TRACE_ENTRY, "%s(%s %p, %p)", __func__, __NULLSTR(objformat), objformat, error);
	
  formatsink = osync_try_malloc0(sizeof(OSyncObjFormatSink), error);
  if (!formatsink)
    return NULL;
	
  /*formatsink->objformat = osync_objformat_ref(objformat);*/
  formatsink->objformat = g_strdup(objformat);
  formatsink->config = NULL;
  formatsink->ref_count = 1;
	
  osync_trace(TRACE_EXIT, "%s: %p", __func__, formatsink);
  return formatsink;
}

OSyncObjFormatSink *osync_objformat_sink_ref(OSyncObjFormatSink *sink)
{
  osync_assert(sink);
	
  g_atomic_int_inc(&(sink->ref_count));

  return sink;
}

void osync_objformat_sink_unref(OSyncObjFormatSink *sink)
{
  osync_assert(sink);
	
  if (g_atomic_int_dec_and_test(&(sink->ref_count))) {

    if (sink->objformat)
      g_free(sink->objformat);
			
    if (sink->config)
      g_free(sink->config);
		
    g_free(sink);
  }
}

const char *osync_objformat_sink_get_objformat(OSyncObjFormatSink *sink)
{
  osync_assert(sink);
  return sink->objformat;
}

const char *osync_objformat_sink_get_config(OSyncObjFormatSink *sink)
{
  osync_assert(sink);
  return sink->config;
}

void osync_objformat_sink_set_config(OSyncObjFormatSink *sink, const char *config)
{
  osync_assert(sink);

  if (sink->config)
    g_free(sink->config);

  sink->config = g_strdup(config);
}

