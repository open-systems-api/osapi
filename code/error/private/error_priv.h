// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Status declarations
//
// *****************************************************************************************

#ifndef CODE_ERR_ERRORS_PRIV_H_
#define CODE_ERR_ERRORS_PRIV_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Force baseline before system headers
#include "general/general_baseline.h"

// System headers
#include <stddef.h>

// OSAPI module error information
#include "general/general_types.h"

// Error information
#include "error/error_types.h"
#include "error/private/error_priv_clock.h"
#include "error/private/error_priv_io.h"
#include "error/private/error_priv_ipc.h"
#include "error/private/error_priv_machine.h"
#include "error/private/error_priv_net.h"
#include "error/private/error_priv_os.h"
#include "error/private/error_priv_proc.h"
#include "error/private/error_priv_sec.h"
#include "error/private/error_priv_string.h"
#include "error/private/error_priv_util.h"



// *****************************************************************************************
//
// Section: Error Definitions
//
// *****************************************************************************************

// Generic error definitions

static const char * error_none [] =
{
  "Success",
  NULL
};


struct s_osapi_errors
{
  t_error 		topValue;
  const char ** 	name;
};

static const struct s_osapi_errors osapi_error_strings[ OSAPI_MODULE_MAX ] = {
	    { 1,		error_none 	},
	    { e_string_max, 	string_errors  	},
	    { e_os_max, 	os_errors	},
	    { e_machine_max, 	machine_errors 	},
	    { e_proc_max, 	proc_errors	},
	    { e_clock_max,	clock_errors	},
	    { e_sec_max,	sec_errors	},
	    { e_io_max,		io_errors	},
	    { e_util_max,	util_errors	},
	    { e_ipc_max,	ipc_errors	},
	    { e_net_max,	net_errors	},
};


#endif /* CODE_ERR_ERRORS_PRIV_H_ */