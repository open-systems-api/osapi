// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	OS Error type declarations
//
// *****************************************************************************************

#ifndef OSAPI_ERROR_OS_H_
#define OSAPI_ERROR_OS_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include General error definitions
#include "error/error_types.h"

// Include own error definitions

#define osapi_error_os_X(a, b, c) a b,
enum osapi_error_os_E {
	  #include "error/mappings/table_os.h"
};
#undef osapi_error_os_X


#endif /* OSAPI_ERROR_OS_H_ */
