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

#ifndef _OPENSYNC_CONVERTER_H_
#define _OPENSYNC_CONVERTER_H_

/**
 * @defgroup OSyncConverterAPI OpenSync Converter
 * @ingroup OSyncFormatPublic
 * @brief Functions for creating and managing object format converters
 * 
 */
/*@{*/

/** Type of the converter */
typedef enum {
	/** Simple converter */
	OSYNC_CONVERTER_CONV = 1,
	/** Encapsulator */
	OSYNC_CONVERTER_ENCAP = 2,
	/** Desencapsulator */
	OSYNC_CONVERTER_DECAP = 3,
	/** Detector */
	OSYNC_CONVERTER_DETECTOR = 4
} OSyncConverterType;

typedef osync_bool (* OSyncFormatDetectFunc) (const char *data, int size, void *userdata);
typedef osync_bool (* OSyncFormatConvertFunc) (char *input, unsigned int inpsize, char **output, unsigned int *outpsize, osync_bool *free_input, const char *config, void *userdata, OSyncError **error);
typedef void * (* OSyncFormatConverterInitializeFunc) (const char *config, OSyncError **error);
typedef void (* OSyncFormatConverterFinalizeFunc) (void *userdata);

/**
 * @brief Creates a new converter
 * @param type the type of converter
 * @param sourceformat the source format for the converter
 * @param targetformat the target format for the converter
 * @param convert_func the converter function
 * @param error Pointer to an error struct
 * @returns The pointer to the newly allocated converter or NULL in case of error
 */
OSYNC_EXPORT OSyncFormatConverter *osync_converter_new(OSyncConverterType type, OSyncObjFormat *sourceformat, OSyncObjFormat *targetformat, OSyncFormatConvertFunc convert_func, OSyncError **error);

/**
 * @brief Creates a new detector
 *
 * @param sourceformat the source format for the converter
 * @param targetformat the target format for the converter
 * @param detect_func the detection function
 * @param error Pointer to an error struct
 * @returns The pointer to the newly allocated detector or NULL in case of error
 */
OSYNC_EXPORT OSyncFormatConverter *osync_converter_new_detector(OSyncObjFormat *sourceformat, OSyncObjFormat *targetformat, OSyncFormatDetectFunc detect_func, OSyncError **error);

/*! @brief Increase the reference count on a converter
 * 
 * @param converter Pointer to the converter
 * 
 */
OSYNC_EXPORT OSyncFormatConverter *osync_converter_ref(OSyncFormatConverter *converter);

/*! @brief Decrease the reference count on a converter
 * 
 * @param converter Pointer to the converter
 * 
 */
OSYNC_EXPORT void osync_converter_unref(OSyncFormatConverter *converter);

/**
 * @brief Returns the source format of a converter
 * @param converter Pointer to the converter
 * @returns The source format of the specified converter
 */
OSYNC_EXPORT OSyncObjFormat *osync_converter_get_sourceformat(OSyncFormatConverter *converter);

/**
 * @brief Returns the target format of a converter
 * @param converter Pointer to the converter
 * @returns The target format of the specified converter
 */
OSYNC_EXPORT OSyncObjFormat *osync_converter_get_targetformat(OSyncFormatConverter *converter);

/**
 * @brief Returns the type of a converter
 * @param converter Pointer to the converter
 * @returns The type of the specified converter
 */
OSYNC_EXPORT OSyncConverterType osync_converter_get_type(OSyncFormatConverter *converter);

/**
 * @brief Detects the Object Format of passed OSyncData 
 * @param detector Pointer to the detector 
 * @param data Pointer to OSyncData object which should be detected
 * @returns The detected Object Format or NULL 
 */
OSYNC_EXPORT OSyncObjFormat *osync_converter_detect(OSyncFormatConverter *converter, OSyncData *data);

/**
 * @brief Invokes converter for OSyncData object with passed format converter configuration 
 *
 * @param converter Pointer to the converter 
 * @param data Pointer to OSyncData object which should be detected
 * @param config Format converter configuration
 * @param error Pointer to an error struct
 * @returns TRUE on successful conversion, FALSE on error
 */
OSYNC_EXPORT osync_bool osync_converter_invoke(OSyncFormatConverter *converter, OSyncData *data, const char *config, OSyncError **error);

/**
 * @brief Checks if the Format Converter fits the Object Format of OSyncData object 
 * @param converter Pointer to the converter 
 * @param data Pointer to OSyncData object which should be converted 
 * @returns TRUE if Object Format matches the Converter source format, FALSE otherwise
 */
OSYNC_EXPORT osync_bool osync_converter_matches(OSyncFormatConverter *converter, OSyncData *data);

/**
 * @brief Creates a new converter path
 * @param error Pointer to an error struct
 * @returns The pointer to the newly allocated converter path or NULL in case of error
 */
OSYNC_EXPORT OSyncFormatConverterPath *osync_converter_path_new(OSyncError **error);

/** @brief Increase the reference count on a converter path
 * 
 * @param path Pointer to the converter path
 * @returns Pointer of converter path object
 * 
 */
OSYNC_EXPORT OSyncFormatConverterPath *osync_converter_path_ref(OSyncFormatConverterPath *path);

/** @brief Decrease the reference count on a converter path
 * 
 * @param path Pointer to the converter path
 * 
 */
OSYNC_EXPORT void osync_converter_path_unref(OSyncFormatConverterPath *path);

/** @brief Add a converter to a converter path
 * @param path Pointer to the converter path
 * @param edge Pointer to the converter to add
 */
OSYNC_EXPORT void osync_converter_path_add_edge(OSyncFormatConverterPath *path, OSyncFormatConverter *edge);

/** @brief Returns the number of converters in a converter path
 * @param path Pointer to the converter path
 * @returns the number of converters in the specified path
 */
OSYNC_EXPORT unsigned int osync_converter_path_num_edges(OSyncFormatConverterPath *path);

/** @brief Returns the nth converter in a converter path
 * @param path Pointer to the converter path
 * @param nth The position of the converter to retrieve
 * @returns the converter at the specified index
 */
OSYNC_EXPORT OSyncFormatConverter *osync_converter_path_nth_edge(OSyncFormatConverterPath *path, unsigned int nth);

/** @brief Returns configuration for converter path 
 * @param path Pointer to the converter path
 * @returns The converter path configuration 
 */
OSYNC_EXPORT const char *osync_converter_path_get_config(OSyncFormatConverterPath *path);

/*! @brief Sets the configuration for converter path 
 * @param path Pointer to the converter path
 * @param config The converter path configuration
 */
OSYNC_EXPORT void osync_converter_path_set_config(OSyncFormatConverterPath *path, const char *config);

/**
 * @brief Sets the initialize function of a converter
 * @param converter Pointer to the converter
 * @param initialize_func Pointer to the initialize function
 */
OSYNC_EXPORT void osync_converter_set_initialize_func(OSyncFormatConverter *converter, OSyncFormatConverterInitializeFunc initialize_func);

/**
 * @brief Sets the finalize function of a converter
 * @param converter Pointer to the converter
 * @param initialize_func Pointer to the finialize function
 */
OSYNC_EXPORT void osync_converter_set_finalize_func(OSyncFormatConverter *converter, OSyncFormatConverterFinalizeFunc finalize_func);

/**
 * @brief Invokes initialize function of a converter 
 *
 * @param converter Pointer to the converter which should be initalized
 * @param config configuration
 * 
 * @todo config is not used currently. Should be usesd in the future to pass a directoy for xml format schema location
 */
OSYNC_EXPORT void osync_converter_initialize(OSyncFormatConverter *converter, const char *config, OSyncError **error);

/**
 * @brief Invokes finalize function of a converter 
 *
 * @param converter Pointer to the converter which should be finalized
 */
OSYNC_EXPORT void osync_converter_finalize(OSyncFormatConverter *converter);

/*@}*/

#endif //_OPENSYNC_CONVERTER_H_
