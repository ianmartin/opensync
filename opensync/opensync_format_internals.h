/**
 * @defgroup OSyncConvPrivate OpenSync Conversion Internals
 * @ingroup OSyncPrivate
 * @brief The private API of opensync
 * 
 * This gives you an insight in the private API of opensync.
 * 
 */
/*@{*/

/*! @brief The environment used for conversions
 */
struct OSyncFormatEnv {
	GList *objtypes; /** A list of object types */
	GList *objformats; /** A List of formats */
	GList *converters; /** A list of available converters */
	GList *filter_functions; /* A list of filter functions */
	GList *extensions; /* A list of extensions */
};

/*! @brief Represent a abstract object type (like "contact")
 */
struct OSyncObjType {
	char *name;
	GList *formats;
	GList *converters;
	OSyncFormatEnv *env;
	osync_bool needs_slow_sync;
	OSyncObjFormat *common_format;
};

/*! @brief Represent a format for a object type
 */
struct OSyncObjFormat {
	char *name;
	OSyncFormatEnv *env;
	OSyncObjType *objtype;
	//GList *extensions;
	OSyncFormatCompareFunc cmp_func;
	OSyncFormatMergeFunc merge_func;
	OSyncFormatDuplicateFunc duplicate_func;
	OSyncFormatCopyFunc copy_func;
	OSyncFormatCreateFunc create_func;
	OSyncFormatDestroyFunc destroy_func;
	OSyncFormatPrintFunc print_func;
};

/*! @brief Represent a converter from one format to another
 */
struct OSyncFormatConverter {
	OSyncObjFormat *source_format;
	OSyncObjFormat *target_format;
	OSyncFormatConvertFunc convert_func;
	OSyncFormatDetectDataFunc detect_func;
	OSyncFormatConverterInitFunc init_func;
	OSyncFormatConverterFinalizeFunc fin_func;
	ConverterType type;
	//void *conv_data;
};

/*! @brief Represent a detector for a given format
 */
typedef struct OSyncDataDetector {
	const char *sourceformat;
	const char *targetformat;
	OSyncFormatDetectDataFunc detect_func;
} OSyncDataDetector;

/*! @brief An extension to a format
 */
typedef struct OSyncFormatExtension {
	OSyncObjFormat *from_format;
	OSyncObjFormat *to_format;
	char *name;
	OSyncFormatConvertFunc conv_func;
	OSyncFormatExtInitFunc init_func;
} OSyncFormatExtension;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef struct OSyncObjFormatSink {
	OSyncObjFormat *format;
	OSyncFormatFunctions functions;
	char *extension_name;
	struct OSyncObjTypeSink *objtype_sink;
} OSyncObjFormatSink;

typedef struct OSyncObjTypeSink {
	OSyncMember *member;
	OSyncObjType *objtype;
	osync_bool write;
	osync_bool read;
	osync_bool enabled;
	GList *formatsinks;
	OSyncObjFormatSink *selected_format;
	GList *properties;
} OSyncObjTypeSink;

typedef struct OSyncObjTypeTemplate {
	const char *name;
	GList *formats;
} OSyncObjTypeTemplate;

typedef struct OSyncObjFormatTemplate {
	const char *name;
	const char *objtype;
	char *extension_name;
	osync_bool (* commit_change) (OSyncContext *, OSyncChange *);
	osync_bool (* access) (OSyncContext *, OSyncChange *);
	OSyncFormatCompareFunc cmp_func;
	OSyncFormatMergeFunc merge_func;
	OSyncFormatDuplicateFunc duplicate_func;
	OSyncFormatCopyFunc copy_func;
	OSyncFormatCreateFunc create_func;
	OSyncFormatDestroyFunc destroy_func;
	OSyncFormatPrintFunc print_func;
} OSyncObjFormatTemplate;

typedef struct OSyncConverterTemplate {
	const char *source_format;
	const char *target_format;
	OSyncFormatConvertFunc convert_func;
	ConverterType type;
	OSyncFormatConverterInitFunc init_func;
	OSyncFormatConverterFinalizeFunc fin_func;
} OSyncConverterTemplate;

typedef struct OSyncFormatExtensionTemplate {
	char *from_formatname;
	char *to_formatname;
	char *name;
	OSyncFormatExtInitFunc init_func;
} OSyncFormatExtensionTemplate;

/** A target function for osync_conv_find_path_fn() */
typedef osync_bool (*OSyncPathTargetFn)(const void *data, OSyncObjFormat *fmt);

osync_bool osync_conv_find_path_fmtlist(OSyncFormatEnv *env, OSyncChange *start, GList/*OSyncObjFormat * */ *targets, GList **retlist);

osync_bool osync_conv_convert_fn(OSyncFormatEnv *env, OSyncChange *change, OSyncPathTargetFn target_fn, const void *fndata, const char *extension_name, OSyncError **error);
osync_bool osync_conv_convert_fmtlist(OSyncFormatEnv *env, OSyncChange *change, GList/*OSyncObjFormat * */ *targets);
osync_bool osync_change_convert_member_sink(OSyncFormatEnv *env, OSyncChange *change, OSyncMember *memb, OSyncError **error);
OSyncDataDetector *osync_env_find_detector(OSyncEnv *env, const char *sourcename, const char *targetname);
osync_bool osync_conv_objtype_is_any(const char *objstr);
OSyncFormatExtensionTemplate *osync_env_find_extension_template(OSyncEnv *env, const char *formatname);
OSyncFormatExtension *osync_conv_find_extension(OSyncFormatEnv *env, OSyncObjFormat *from_format, OSyncObjFormat *to_format, const char *extension_name);
OSyncChange *osync_converter_invoke_decap(OSyncFormatConverter *converter, OSyncChange *change, osync_bool *free_output);

#endif

/*@}*/
