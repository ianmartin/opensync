#include <opensync/opensync.h>
#include <opensync/opensync_internals.h>
#include <sys/stat.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <config.h>
#include <check.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

typedef struct mock_env {
        char *path;
        OSyncMember *member;
        GDir *dir;
        OSyncHashTable *hashtable;
        osync_bool committed_all;
} mock_env;
