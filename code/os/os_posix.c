/*
 * os_posix.c
 *
 *  Created on: 01/04/2017
 *      Author: joao
 */

#include <string.h>
#include <error/error_os.h>
#include <os/os.h>

t_status os_posix_info_get( t_osInfo * p_osInfo )
{
 t_status	st;
 struct utsname	info;

 status_reset( & st );

 errno = 0;
 if( p_osInfo == (t_osInfo *) 0 )
     status_iset( OSAPI_MODULE_OS, __func__, e_os_params, &st );
 else
   {
     if( uname( &info ) )
	 status_eset( OSAPI_MODULE_OS, __func__, errno, &st );
     else
       {
	 strncpy( p_osInfo->kernel, 	info.sysname,		OSAPI_OS_MAX_KERNEL_NAME	);
	 strncpy( p_osInfo->node,	info.nodename,		OSAPI_OS_MAX_NODE_NAME		);
	 strncpy( p_osInfo->release,	info.release,		OSAPI_OS_MAX_RELEASE_NAME	);
	 strncpy( p_osInfo->version,	info.version, 		OSAPI_OS_MAX_VERSION		);
	 strncpy( p_osInfo->machine,	info.machine, 		OSAPI_OS_MAX_MACHINE_NAME	);
       }
   }

 return st;
}


