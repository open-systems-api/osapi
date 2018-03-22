/*
 * os_linux.c
 *
 *  Created on: 12/02/2018
 *      Author: joao
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <error/error_os.h>
#include <os/os.h>

t_status os_info_provider_get( t_osInfo * p_osInfo )
{
  t_status	st;
  char *	line 	= NULL;
  size_t 	len 	= 0;
  ssize_t 	nread;

  status_reset( & st );

  if( p_osInfo == (t_osInfo *) 0 )
      status_iset( OSAPI_MODULE_OS, __func__, e_os_params, &st );
  else
    {
      FILE * fp = fopen( OSAPI_OS_RELEASE_INFO_FILE, "r" );
      if( fp == (FILE *) 0 )
	  status_eset( OSAPI_MODULE_OS, __func__, errno, &st );
      else
	{
	  // Read Distribution file

          while( ( nread = getline( &line, &len, fp ) ) != -1 )
               {
		 if( strncmp( line, "NAME=", 5 ) == 0 )		// Found Provider name
		   {
		     // Copy the string property value but removing the commas
		     strncpy( p_osInfo->provider, &line[ 6 ], nread - 8 );
		     continue;
		   }
		 if( strncmp( line, "VERSION_ID=", 11 ) == 0 )	// Found Provider Release
		   {
		     // Copy the string property value but removing the commas
		     strncpy( p_osInfo->provider_release, &line[ 12 ], nread - 14 );
		     continue;
		   }
		 // Other Distribution properties can be added here...
               }

          free( line );
          fclose( fp );
	}
    }

  return st;
}

t_status os_info_get( t_osInfo * p_osInfo )
{
  t_status	st;

  status_reset( & st );

  if( p_osInfo == (t_osInfo *) 0 )
      status_iset( OSAPI_MODULE_OS, __func__, e_os_params, &st );
  else
    {
      st = os_posix_info_get( p_osInfo );
      if( status_success( st ) )
	{
	  errno = 0;
	  if( getdomainname(p_osInfo->domain, OSAPI_OS_MAX_DOMAIN_NAME ) == -1 )
	      status_eset( OSAPI_MODULE_OS, __func__, errno, &st );
	}

      // For Linux, get the distribution and version
      if( status_success( st ) )
	  st = os_info_provider_get( p_osInfo );
    }

  return st;
}