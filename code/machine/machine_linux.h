// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	HW Linux OS declarations
//
// *****************************************************************************************

#ifndef MACHINE_MACHINE_LINUX_H_
#define MACHINE_MACHINE_LINUX_H_

// Only relevant is OS is Linux
#ifdef OS_LINUX


// Make sure that header is easily imported from c++
#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include System headers
#include <ifaddrs.h>

// Generic OSAPI includes

// Own headers
#include "machine/machine_types_linux.h"

// *****************************************************************************************
//
// Section: Function Declarations
//
// *****************************************************************************************

static t_status copy_ip			( struct sockaddr * saddress, void * address	);
static t_status fill_ip_structure	( struct ifaddrs * address, t_ip * ip		);


// End of header with C++ declaration
#ifdef __cplusplus
}
#endif

#endif	// End of OS Linux

#endif /* MACHINE_MACHINE_LINUX_H_ */
