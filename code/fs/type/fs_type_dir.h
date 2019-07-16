// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Type declarations for a directory Element
//
// *****************************************************************************************

#ifndef OSAPI_FS_TYPE_DIR_H_
#define OSAPI_FS_TYPE_DIR_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import own headers
#include "fs/fs_platform.h"
#include "fs/type/fs_type_element.h"

// *****************************************************************************************
//
// Section: Type definitions
//
// *****************************************************************************************


/// Structure that holds all file system element information
struct osapi_fs_s_dir
{
  t_element			element;	///< General element information
  t_fs_directoryInfo		dir;		///< Directory element specific information
};

typedef struct osapi_fs_s_dir			t_dir;




#endif /* OSAPI_FS_TYPE_DIR_H_ */
