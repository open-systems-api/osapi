// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Proc Error type declarations
//
// *****************************************************************************************

#ifndef OSAPI_ERROR_PROC_H_
#define OSAPI_ERROR_PROC_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include General error definitions
#include "error/error_types.h"

// Include own error definitions

#define osapi_error_proc_X(a, b, c) a b,
enum osapi_error_proc_E {
	  #include "error/mappings/table_proc.h"
};
#undef osapi_error_proc_X

#endif /* OSAPI_ERROR_PROC_H_ */
