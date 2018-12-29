// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide IO module API
//
// *****************************************************************************************

#ifndef IO_H_
#define IO_H_

// Make sure that header is easily imported from c++
#ifdef __cplusplus
extern "C" {
#endif


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Generic OSAPI includes
#include "general/general.h"
#include "status/status_types.h"

// Common includes
#include <common/types/common_types.h>

// Own declarations
#include "io/io_types.h"
#include "io/io_platform.h"


// *****************************************************************************************
//
// Section: Proc(ess) module API
//
// *****************************************************************************************

#pragma GCC visibility push(default)		// Start of public interface

t_status	io_module_supported		( void 			);

// Directory facilities
t_status	io_directory_change		( t_char *		);

/*
t_status	io_directory_create		( t_char *		);
t_status	io_directory_is			( t_char *		);
t_status	io_directory_getCurrent		( t_char *		);

*/

// File facilities
/*
t_status	io_file_open			( t_char *, t_file *		);
t_status	io_file_close			( t_file			);
t_status	io_file_read			( t_file, t_size, t_stream *	);
t_status	io_file_write			( t_file, t_size, t_stream	);
*/

#pragma GCC visibility pop			// End of public interface

// End of header with C++ declaration
#ifdef __cplusplus
}
#endif


#endif /* IO_H_ */