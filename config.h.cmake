#ifndef _CONFIG_H_OPENSYNC
#define _CONFIG_H_OPENSYNC

#define OPENSYNC_PLUGINDIR "${OPENSYNC_PLUGINDIR}"
#define OPENSYNC_FORMATSDIR "${OPENSYNC_FORMATSDIR}"

#define OPENSYNC_CONFIGDIR "${OPENSYNC_CONFIGDIR}"

#define OPENSYNC_SCHEMASDIR "${OPENSYNC_SCHEMASDIR}"
#define OPENSYNC_DESCRIPTIONSDIR "${OPENSYNC_DESCRIPTIONSDIR}"
#define OPENSYNC_CAPABILITIESDIR "${OPENSYNC_CAPABILITIESDIR}"

#define OPENSYNC_VERSION "${OPENSYNC_VERSION}"

#define OPENSYNC_PLUGINVERSION ${OPENSYNC_PLUGINVERSION}

#cmakedefine OPENSYNC_DEBUG_MODULES 
#cmakedefine OPENSYNC_TRACE

#cmakedefine HAVE_FLOCK

#define OPENSYNC_TESTDATA "${CMAKE_CURRENT_SOURCE_DIR}/tests/data"
#cmakedefine OPENSYNC_UNITTESTS

#endif /* _CONFIG_H_OPENSYNC */
