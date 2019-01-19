// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	General UNIX baseline specification
//
// *****************************************************************************************



#ifndef OSAPI_GENERAL_BASELINE_UNIX_H_
#define OSAPI_GENERAL_BASELINE_UNIX_H_

// Define target UNIX standards
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE	700


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include platform available standards
#include <unistd.h>

#include "general/general_language.h"

// *****************************************************************************************
//
// Section: Platform Baseline definition
//
// *****************************************************************************************

// Define XOPEN && POSIX baselines/constraints
osapi_static_assert( _XOPEN_VERSION == 700,	"Wrong XOPEN version" );
osapi_static_assert( _POSIX_VERSION == 200809L,	"Wrong POSIX version" );


// If compilation reaches this far, them define own POSIX symbol
#define OSAPI_POSIX


#endif /* OSAPI_GENERAL_BASELINE_UNIX_H_ */
