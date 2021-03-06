#include <opensync/opensync.h>
#include <opensync/opensync-data.h>
#include <opensync/opensync-format.h>
#include <opensync/opensync-plugin.h>
#include <opensync/opensync-context.h>
#include <opensync/opensync-helper.h>
#include <opensync/opensync-version.h>
#include <opensync/opensync_list.h>

#include <string.h>

typedef struct {
        OSyncList *sink_envs;
} plugin_environment;

typedef struct {
        OSyncObjTypeSink *sink;
} sink_environment;

static void free_env(plugin_environment *env)
{
	while (env->sink_envs) {
		sink_environment *sinkenv = env->sink_envs->data;

		if (sinkenv->sink)
			osync_objtype_sink_unref(sinkenv->sink);

		env->sink_envs = osync_list_remove(env->sink_envs, sinkenv);
	}

	osync_free(env);
}

static void connect(void *userdata, OSyncPluginInfo *info, OSyncContext *ctx)
{
	osync_trace(TRACE_ENTRY, "%s(%p, %p, %p)", __func__, userdata, info, ctx);
	//Each time you get passed a context (which is used to track
	//calls to your plugin) you can get the data your returned in
	//initialize via this call:
	// plugin_environment *env = (plugin_environment *)userdata;

	//The sink specific userdata you can get with this calls:
	OSyncObjTypeSink *sink = osync_plugin_info_get_sink(info);
	sink_environment *sinkenv = osync_objtype_sink_get_userdata(sink);


	OSyncError *error = NULL;

	/*
	 * Now connect to your devices and report
	 * 
	 * an error via:
	 * osync_context_report_error(ctx, ERROR_CODE, "Some message");
	 * 
	 * or success via:
	 * osync_context_report_success(ctx);
	 * 
	 * You have to use one of these 2 somewhere to answer the context.
	 * 
	 */

	//you can also use the anchor system to detect a device reset
	//or some parameter change here. Check the docs to see how it works
	char *lanchor = NULL;
	//Now you get the last stored anchor from the device
	char *anchorpath = osync_strdup_printf("%s/anchor.db", osync_plugin_info_get_configdir(info));

	if (!osync_anchor_compare(anchorpath, "lanchor", lanchor))
		osync_objtype_sink_set_slowsync(sink, TRUE);

	osync_free(anchorpath);

	osync_context_report_success(ctx);
	osync_trace(TRACE_EXIT, "%s", __func__);
	return;

error:
	osync_context_report_osyncerror(ctx, error);
	osync_trace(TRACE_EXIT_ERROR, "%s: %s", __func__, osync_error_print(&error));
	osync_error_unref(&error);
}

static void get_changes(void *userdata, OSyncPluginInfo *info, OSyncContext *ctx)
{
	osync_trace(TRACE_ENTRY, "%s(%p, %p, %p)", __func__, userdata, info, ctx);

	//plugin_environment *env = (plugin_environment *)userdata;
	OSyncFormatEnv *formatenv = osync_plugin_info_get_format_env(info);
	OSyncObjTypeSink *sink = osync_plugin_info_get_sink(info);
	sink_environment *sinkenv = osync_objtype_sink_get_userdata(sink);

	OSyncError *error = NULL;

	/* Check for Slow-Sync */
	if (osync_objtype_sink_get_slowsync(sinkenv->sink)) {
	}

	/*
	 * Now you can get the changes.
	 * Loop over all changes you get and do the following:
	 */

	do {
		char *uid = osync_strdup("<some uid>");

		//Now get the data of this change
		char *data = NULL;


		/* Determine the "Change Type" of this change (e.g. ADDED, MODIFIED, DELETED, ...) */
		OSyncChangeType changetype  = OSYNC_CHANGE_TYPE_ADDED;

		//Make the new change to report
		OSyncChange *change = osync_change_new(&error);
		if (!change) {
			osync_context_report_osyncwarning(ctx, error);
			osync_error_unref(&error);
			continue;
		}

		//Now set the uid of the object
		osync_change_set_uid(change, uid);
		
		osync_change_set_changetype(change, changetype);
		
		if (changetype == OSYNC_CHANGE_TYPE_UNMODIFIED) {
			osync_free(uid);
			osync_change_unref(change);
			continue;
		}

		osync_free(uid);

		OSyncObjFormat *format = osync_format_env_find_objformat(formatenv, "<objformat>");
		
		OSyncData *odata = osync_data_new(data, 0, format, &error);
		if (!odata) {
			osync_change_unref(change);
			osync_context_report_osyncwarning(ctx, error);
			osync_error_unref(&error);
			continue;
		}

		osync_data_set_objtype(odata, osync_objtype_sink_get_name(sinkenv->sink));

		//Now you can set the data for the object
		osync_change_set_data(change, odata);
		osync_data_unref(odata);

		// just report the change via
		osync_context_report_change(ctx, change);

		osync_change_unref(change);

		osync_free(uid);
	} while(0);

	//Now we need to answer the call
	osync_context_report_success(ctx);
	osync_trace(TRACE_EXIT, "%s", __func__);
}

static void commit_change(void *userdata, OSyncPluginInfo *info, OSyncContext *ctx, OSyncChange *change)
{
	//plugin_environment *env = (plugin_environment *)userdata;

	OSyncObjTypeSink *sink = osync_plugin_info_get_sink(info);
	sink_environment *sinkenv = osync_objtype_sink_get_userdata(sink);
	
	/*
	 * Here you have to add, modify or delete a object
	 * 
	 */
	switch (osync_change_get_changetype(change)) {
		case OSYNC_CHANGE_TYPE_DELETED:
			//Delete the change
			//Dont forget to answer the call on error
			break;
		case OSYNC_CHANGE_TYPE_ADDED:
			//Add the change
			//Dont forget to answer the call on error
			break;
		case OSYNC_CHANGE_TYPE_MODIFIED:
			//Modify the change
			//Dont forget to answer the call on error
			break;
		default:
			;
	}

	//Answer the call
	osync_context_report_success(ctx);
}

static void sync_done(void *userdata, OSyncPluginInfo *info, OSyncContext *ctx)
{
	/*
	 * This function will only be called if the sync was successful
	 */
	OSyncError *error = NULL;
	OSyncObjTypeSink *sink = osync_plugin_info_get_sink(info);
	sink_environment *sinkenv = osync_objtype_sink_get_userdata(sink);
	
	//If we use anchors we have to update it now.
	//Now you get/calculate the current anchor of the device
	char *lanchor = NULL;
	char *anchorpath = osync_strdup_printf("%s/anchor.db", osync_plugin_info_get_configdir(info));
	osync_anchor_update(anchorpath, "lanchor", lanchor);
	osync_free(anchorpath);
	
	//Answer the call
	osync_context_report_success(ctx);
	return;
error:
	osync_context_report_osyncerror(ctx, error);
	osync_error_unref(&error);
	return;
}

static void disconnect(void *userdata, OSyncPluginInfo *info, OSyncContext *ctx)
{
	OSyncObjTypeSink *sink = osync_plugin_info_get_sink(info);
	sink_environment *sinkenv = osync_objtype_sink_get_userdata(sink);
	
	//Close all stuff you need to close
	
	//Answer the call
	osync_context_report_success(ctx);
}

static void finalize(void *userdata)
{
	plugin_environment *env = (plugin_environment *)userdata;

	//Free all stuff that you have allocated here.
	free_env(env);
}


static void *initialize(OSyncPlugin *plugin, OSyncPluginInfo *info, OSyncError **error)
{
	/*
	 * get the config
	 */
	OSyncPluginConfig *config = osync_plugin_info_get_config(info);
	if (!config) {
		osync_error_set(error, OSYNC_ERROR_GENERIC, "Unable to get config.");
		goto error;
	}
	/*
	 * You need to specify the <some name>_environment somewhere with
	 * all the members you need
	*/
	plugin_environment *env = osync_try_malloc0(sizeof(plugin_environment), error);
	if (!env)
		goto error;

	env->sink_envs = NULL;
	
	osync_trace(TRACE_INTERNAL, "The config: %s", osync_plugin_info_get_config(info));

	/* 
	 * Process the config here and set the options on your environment
	*/
	/*
	 * Process plugin specific advanced options 
	 */
	OSyncList *optslist = osync_plugin_config_get_advancedoptions(config);
	for (; optslist; optslist = optslist->next) {
		OSyncPluginAdvancedOption *option = optslist->data;

		const char *val = osync_plugin_advancedoption_get_value(option);
		const char *name = osync_plugin_advancedoption_get_name(option);

		if (!strcmp(name,"<your-option>")) {
			if (!strcmp(val, "<your-value>")) {
				/*
				 * set a varaible to a specific value
				 */;
			}
		}
	}
	/*
	 * Process Ressource options
	 */
	int i, numobjs = osync_plugin_info_num_objtypes(info);
	for (i = 0; i < numobjs; i++) {
		sink_environment *sinkenv = osync_try_malloc0(sizeof(sink_environment), error);
		if (!sinkenv)
			goto error_free_env;

		sinkenv->sink = osync_plugin_info_nth_objtype(info, i);
		osync_assert(sinkenv->sink);

		const char *objtype = osync_objtype_sink_get_name(sinkenv->sink);
		OSyncPluginResource *res = osync_plugin_config_find_active_resource(config, objtype);
		
		/* get objformat sinks */
		OSyncList *s = osync_plugin_resource_get_objformat_sinks(res);
		for (; s; s = s->next) {
			OSyncObjFormatSink *fsink = s->data; // there could be only one sink
			const char *objformat = osync_objformat_sink_get_objformat(fsink);
			osync_assert(objformat);
			osync_trace(TRACE_INTERNAL, "objtype %s has objformat %s", objtype, objformat);
		}	

		/* Every sink can have different functions ... */
		OSyncObjTypeSinkFunctions functions;
		memset(&functions, 0, sizeof(functions));
		functions.connect = connect;
		functions.disconnect = disconnect;
		functions.get_changes = get_changes;
		functions.commit = commit_change;
		functions.sync_done = sync_done;

		/* We pass the OSyncFileDir object to the sink, so we dont have to look it up
		 * again once the functions are called */
		osync_objtype_sink_set_functions(sinkenv->sink, functions, sinkenv);
		
		env->sink_envs = osync_list_append(env->sink_envs, sinkenv);
	}
	
	//Now your return your struct.
	return (void *) env;

error_free_env:
	free_env(env);
error:
	osync_trace(TRACE_EXIT_ERROR, "%s: %s", __func__, osync_error_print(error));
	return NULL;
}

/* Here we actually tell opensync which sinks are available. */
static osync_bool discover(void *userdata, OSyncPluginInfo *info, OSyncError **error)
{
	osync_trace(TRACE_ENTRY, "%s(%p, %p, %p)", __func__, userdata, info, error);

//	plugin_environment *env = (plugin_environment *)userdata;

	// Report avaliable sinks...
	OSyncObjTypeSink *sink = osync_plugin_info_find_objtype(info, "<objtype e.g. note>");
	if (!sink) {
		return FALSE;
	}
	osync_objtype_sink_set_available(sink, TRUE);
	
	OSyncVersion *version = osync_version_new(error);
	osync_version_set_plugin(version, "<your plugin-name>");
	//osync_version_set_version(version, "version");
	//osync_version_set_modelversion(version, "version");
	//osync_version_set_firmwareversion(version, "firmwareversion");
	//osync_version_set_softwareversion(version, "softwareversion");
	//osync_version_set_hardwareversion(version, "hardwareversion");
	osync_plugin_info_set_version(info, version);
	osync_version_unref(version);

	osync_trace(TRACE_EXIT, "%s", __func__);
	return TRUE;
}


osync_bool get_sync_info(OSyncPluginEnv *env, OSyncError **error)
{
	//Now you can create a new plugin information and fill in the details
	//Note that you can create several plugins here
	OSyncPlugin *plugin = osync_plugin_new(error);
	if (!plugin)
		goto error;
	
	//Tell opensync something about your plugin
	osync_plugin_set_name(plugin, "short name, maybe < 15 chars");
	osync_plugin_set_longname(plugin, "long name. maybe < 50 chars");
	osync_plugin_set_description(plugin, "A longer description. < 200 chars");

	//Now set the function we made earlier
	osync_plugin_set_initialize(plugin, initialize);
	osync_plugin_set_finalize(plugin, finalize);
	osync_plugin_set_discover(plugin, discover);

	osync_plugin_env_register_plugin(env, plugin);
	osync_plugin_unref(plugin);

	return TRUE;
error:
	osync_trace(TRACE_ERROR, "Unable to register: %s", osync_error_print(error));
	osync_error_unref(error);
	return FALSE;
}

int get_version(void)
{
	return 1;
}
