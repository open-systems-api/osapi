// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide enum to string mappings for errors on the Filesystem module
//
// *****************************************************************************************

osapi_fs_error_X( osapi_fs_error_none,    = OSAPI_ERROR_BASE,		OSAPI_ERROR_STRING_NONE		)

osapi_fs_error_X( osapi_fs_error_generic, = OSAPI_ERROR_GENERIC,	OSAPI_ERROR_STRING_GENERIC	)
osapi_fs_error_X( osapi_fs_error_support, = OSAPI_ERROR_SUPPORT,	OSAPI_ERROR_STRING_SUPPORT	)
osapi_fs_error_X( osapi_fs_error_params,  = OSAPI_ERROR_INVPARAM,	OSAPI_ERROR_STRING_INVPARAM	)
osapi_fs_error_X( osapi_fs_error_unknown, = OSAPI_ERROR_UNKNOWN,	OSAPI_ERROR_STRING_UNKNOWN	)
osapi_fs_error_X( osapi_fs_error_invopenmode, 			,	"Invalid open mode"		)
osapi_fs_error_X( osapi_fs_error_fopen, 			,	"File is not opened"		)
osapi_fs_error_X( osapi_fs_error_fio, 			,		"File IO error"			)
osapi_fs_error_X( osapi_fs_error_notDirectory, 		,		"Path name is not a directory"	)
osapi_fs_error_X( osapi_fs_error_dopen, 		,		"Directory is not open"		)
osapi_fs_error_X( osapi_fs_error_dclose, 		,		"Directory is not closed"	)
osapi_fs_error_X( osapi_fs_error_notLink, 		,		"Path name is not a link"	)

osapi_fs_error_X( osapi_fs_error_max, ,					OSAPI_ERROR_STRING_UNKNOWN	)
