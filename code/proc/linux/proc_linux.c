// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Proc module using a Linux implementation
//
// *****************************************************************************************

// Only relevant is OS is Linux
#ifdef OS_LINUX

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Force baseline before system headers
#include "general/general_baseline.h"

// System includes <here>

// Generic OSAPI includes
#include "general/general.h"
#include "common/common.h"

// Include own headers
#include "proc/proc.h"
#include "error/modules/error_os.h"
#include "proc/posix/proc_posix.h"
#include "proc/linux/proc_linux.h"


// *****************************************************************************************
//
// Section: Function definition
//
// *****************************************************************************************

t_status proc_library_load( char * pathname, char * options[], t_library * p_library )
{
  int	opt = 0;

  opt = common_options_get( lib_options, options );

  return posix_library_load( pathname, opt, p_library );
}



#endif	// End of OS Linux
