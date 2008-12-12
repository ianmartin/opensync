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

#ifndef _OPENSYNC_FORMAT_ENV_PRIVATE_H_
#define _OPENSYNC_FORMAT_ENV_PRIVATE_H_

/**
 * @defgroup OSyncFormatEnvPrivateAPI OpenSync Format Environment Private
 * @ingroup OSyncFormatPrivate
 * @brief The priavte API of the OpenSync Format Environment
 * 
 */
/*@{*/

/*! @brief Loads the modules from a given directory
 * 
 * Loads all modules from a directory into a osync environment
 * 
 * @param env Pointer to a OSyncFormatEnv environment
 * @param path The path where to look for plugins, NULL for the default sync module directory
 * @param must_exist If set to TRUE, this function will return an error if the directory does not exist
 * @param error Pointer to a error struct to return an error
 * @returns TRUE on success, FALSE otherwise
 * 
 */
static osync_bool osync_format_env_load_modules(OSyncFormatEnv *env, const char *path, osync_bool must_exist, OSyncError **error);

/** @brief Initialize all converters
 * 
 * Calls the initialize function of all converters
 * 
 * @param env Pointer to a OSyncFormatEnv environment
 * @param error Pointer to a error struct to return an error
 */
static void osync_format_env_converter_initialize(OSyncFormatEnv *env, OSyncError **error);

/** @brief Finalize all converters
 * 
 * Calls the finalize function of all converters to free converter specific data
 * 
 * @param env Pointer to a OSyncFormatEnv environment
 */
static void osync_format_env_converter_finalize(OSyncFormatEnv *env);

/** Compare the distance of two vertices
 *
 * First, try to minimize the losses. Then,
 * try to minimize the conversions between
 * different objtypes. Then, try to minimize
 * the total number of conversions.
 */
static int osync_format_converter_path_vertice_compare_distance(const void *a, const void *b);

/** Function used on a path search OSyncFormatConverterPathVertice objformat to check if it matches an OSyncList of OSyncObjFormatSinks 
 * @param data List of OSyncObjFormatSinks
 * @param fmt format to compare with
 * @see osync_conv_find_path_fn(), osync_change_convert_fmtnames()
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static osync_bool osync_format_converter_path_vertice_target_fn_format_sinks(const void *data, OSyncObjFormat *fmt);

/** Function used on path search objformat of data to check if it matches a single format
 * @param data source OSyncObjFormat 
 * @param fmt format to compare with
 * @see osync_conv_find_path_fn(), osync_change_convert()
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static osync_bool osync_format_converter_path_vertice_target_fn_simple(const void *data, OSyncObjFormat *fmt);

/** Function used on a tree list of unused converters to check if there remains any that accomplish an OSyncList of OSyncObjFormatSinks 
 * @param data list of OSyncFormatConverter
 * @see osync_conv_find_path_fn(), osync_change_convert_fmtnames()
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static osync_bool osync_format_converter_tree_target_fn_format_sinks_reached_lastconverter(const void *data, OSyncFormatConverterTree *tree);

/** Function used on a tree list of unused converters to check if there remains one that match a single format
 *
 * @see osync_conv_find_path_fn(), osync_change_convert()
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static osync_bool osync_format_converter_tree_target_fn_simple_reached_lastconverter(const void *data, OSyncFormatConverterTree *tree);
/**
 * @brief Creates a new OSyncFormatConverterPathVertice
 * @param error An error struct
 * @return Returns the new OSyncFormatConverterPathVertice
 */
static OSyncFormatConverterPathVertice *osync_format_converter_path_vertice_new(OSyncError **error);

/** 
 * @brief Increment a OSyncFormatConverterPathVertice reference count
 * @param vertice Pointer to the OSyncFormatConverterPathVertice
 * @return Returns the OSyncFormatConverterPathVertice
 */
static OSyncFormatConverterPathVertice *osync_format_converter_path_vertice_ref(OSyncFormatConverterPathVertice *vertice);

/** 
 * @brief Dereference a OSyncFormatConverterPathVertice
 * @param vertice Pointer to the OSyncFormatConverterPathVertice
 */
static void osync_format_converter_path_vertice_unref(OSyncFormatConverterPathVertice *vertice);

/** 
 * @brief
 * Concepts :
 * - "Detectors" are cheap converters in that all they do is merely check that the data conforms to a given detection function.
 * They are also automatically two ways in that they register their opposite when created.
 * They can also be used to prevent a conversion for a non detector converter which provides the same conversion.
 *
 * Internals :
 * We assume that there is at least a detector converter for this conversion. In theory this is not true  : there is at least
 * the provided converter which is likely not a detector and there could be no detector at all. Though in practice the implementation
 * behaves well as we seek all converters (including the provided one) for a "non detector" one. Then we give preference to this
 * non detector converter (though we always seek for a detector that provides the same conversion before telling this "non detector"
 * converter is valid).
 * 
 * @param ve Pointer to OSyncFormatConverterPathVertice
 * @param env Pointer to OSyncFormatEnv
 * @param converter Pointer to OSyncFormatConverter
 * @return Returns a boolean telling if the current OSyncFormatConverterPathVertice can be converted with the provided converter
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static osync_bool osync_format_converter_path_vertice_validate_path_with_detector(OSyncFormatConverterPathVertice *ve, OSyncFormatEnv *env, OSyncFormatConverter *converter);

/**
 * @brief
 * Returns a new reference to the OSyncFormatConverterPathVertice. The reference
 * should be dropped using deref_vertice(), later.
 * 
 * @param env Pointer to OSyncFormatEnv
 * @param tree Pointer to OSyncFormatConverterTree
 * @param ve Pointer to OSyncFormatConverterPathVertice
 * @param error An error struct
 * @return Returns a neighbour of the OSyncFormatConverterPathVertice ve
 * 
 * @todo maybe this function should be renamed to clarify the functionality
 */
static OSyncFormatConverterPathVertice *osync_format_converter_path_vertice_get_next_vertice_neighbour(OSyncFormatEnv *env, OSyncFormatConverterTree *tree, OSyncFormatConverterPathVertice *ve, OSyncError **error);

/**
 * @brief Frees a OSyncFormatConverterTree
 * @param tree OSyncFormatConverterTree which should be freed
 */
static void osync_converter_tree_free(OSyncFormatConverterTree *tree);

/** 
 * @brief Search for the shortest path of conversions to one or more formats
 *
 * This function search for the shortest path of conversions
 * that can be made to a change, considering possible detections
 * that may be necessary. The target is given by a function
 * that check if a given format is a 'target OSyncFormatConverterPathVertice' or not. The
 * function is used to allow the search path code to be used
 * to search for 'objtype detection', search for the path
 * for an available sink for a format, and maybe other uses.
 *
 * There is a limitation however. To prevent
 * 
 * The list returned on path_edges should be freed by the caller.
 *
 * Note: NEVER use the detection/conversion functions on
 *       CHANGE_DELETED changes. Converting and detecting data
 *       on changes that have no data doesn't make sense
 *
 * @param env Pointer to a OSyncFormatEnv environment
 * @param sourcedata Pointer to OSyncData
 * @param target_fn
 * @param last_converter_fn
 * @param fndata
 * @param preferred_format format which should be preferred in the path calculation
 * @param error An error struct
 * @see osync_conv_convert_fn(), osync_change_convert(),
 *      osync_conv_convert_fmtlist(), osync_change_convert_member_sink()
 *
 * @see target_fn_fmtlist(), target_fn_fmtnames(),
 *      target_fn_simple(), target_fn_fmtname(),
 *      target_fn_membersink(), target_fn_no_any()
 */
static OSyncFormatConverterPath *osync_format_env_find_path_fn(OSyncFormatEnv *env, OSyncData *sourcedata, OSyncPathTargetFn target_fn, OSyncTargetLastConverterFn last_converter_fn, const void *fndata, const char * preferred_format, OSyncError **error);


/*@}*/

#endif /* _OPENSYNC_FORMAT_ENV_PRIVATE_H_ */
