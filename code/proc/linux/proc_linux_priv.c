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

// Increase baseline with Linux specific functionality
#define __USE_MISC 1
#define _GNU_SOURCE
#define __USE_GNU

// System includes <here>
#include <link.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <dlfcn.h>
#include <libgen.h>

// Generic OSAPI includes
#include "general/general.h"
#include "common/common.h"

// Include own headers
#include "error/modules/error_proc.h"
#include "proc/linux/proc_linux_priv.h"


// *****************************************************************************************
//
// Section: Macros/Constant definitions
//
// *****************************************************************************************

const char * OSAPI_FS_PROC_NAME			= "/proc";

struct library_release_data
{
  const t_char	*	libname;
  t_size		size;
  char *		release;
};

// *****************************************************************************************
//
// Section: Internal Function declarations
//
// *****************************************************************************************


static int linux_callback_count_libraries	( struct dl_phdr_info * info, size_t size, void * data );
static int linux_callback_get_libraries		( struct dl_phdr_info * info, size_t size, void * data );
static int linux_callback_get_library		( struct dl_phdr_info * info, size_t size, void * data );



// *****************************************************************************************
//
// Section: Function definition
//
// *****************************************************************************************


t_status get_id_members( int target, t_pid target_id, t_size nmembers, t_size * p_nFoundMembers, t_pid (* p_members)[] )
{
 t_status		st;
 t_proc_info		pinfo;
 t_pid			pid, match_id;
 t_size			current 	= 0;
 struct dirent *	p_dir_entry	= NULL;
 DIR * 			p_dir		= NULL;

 status_reset( & st );

 p_dir = opendir( OSAPI_FS_PROC_NAME );

 while( ( p_dir_entry = readdir( p_dir ) ) )
      {
        if( ( strcmp( p_dir_entry->d_name, "."  ) == 0) ||
            ( strcmp( p_dir_entry->d_name, ".." ) == 0)  )
	      continue;

            // Make sure that the directory entry is not composed of initial numbers, e.g. 12something
            if( ! common_string_isDigit( p_dir_entry->d_name ) )
        	continue;

	    pid = (t_pid) atoi( p_dir_entry->d_name );

	    if( pid >= 0 )	// Check if process is valid
	      {
		st = parse_linux_proc_stat_file( pid, & pinfo );

		if( status_success( st ) && current < nmembers )
		  {
		    match_id = -1;
		    switch( target )
			  {
			    case e_proc_target_parent:	match_id = pinfo.id.ppid; 	break;
			    case e_proc_target_pgroup:	match_id = pinfo.id.pgrp; 	break;
			    case e_proc_target_session:	match_id = pinfo.id.session; 	break;

			    default: break;	// Do Nothing
			  }

		    if( match_id == target_id )	(*p_members)[ current++ ] = pid;
		  }
	      }
          }

 closedir( p_dir );
 *p_nFoundMembers = current;

 return st;
}


t_status count_proc_members( int target, t_pid target_id, t_size * p_number )
{
 t_status st;
 t_proc_info		pinfo;
 t_pid			pid, match_id;
 t_size			current 	= 0;
 struct dirent *	p_dir_entry	= NULL;
 DIR * 			p_dir		= NULL;

 status_reset( & st );

 if( p_number == (t_size *) 0 )
     status_iset( OSAPI_MODULE_PROC, __func__, osapi_proc_error_params, &st );
 else
   {
     p_dir = opendir( OSAPI_FS_PROC_NAME );

     while( ( p_dir_entry = readdir( p_dir ) ) )
          {
	    if( ( strcmp( p_dir_entry->d_name, "."  ) == 0) ||
		( strcmp( p_dir_entry->d_name, ".." ) == 0)  )
	        continue;

            // Make sure that the directory entry is not composed of initial numbers, e.g. 12something
            if( ! common_string_isDigit( p_dir_entry->d_name ) )
        	continue;

	    pid = (t_pid) atoi( p_dir_entry->d_name );

	    if( pid >= 0 )	// Check if process is valid
	      {
		st = parse_linux_proc_stat_file( pid, & pinfo );

		if( status_success( st ) )
		  {
		    match_id = -1;
		    switch( target )
			  {
			    case e_proc_target_parent:	match_id = pinfo.id.ppid; 	break;
			    case e_proc_target_pgroup:	match_id = pinfo.id.pgrp; 	break;
			    case e_proc_target_session:	match_id = pinfo.id.session; 	break;

			    default: break;	// Do Nothing
			  }

		    if( match_id == target_id ) 	current++;
		  }
	      }
          }

     closedir( p_dir );
   }

 *p_number = current;

 return st;
}


static int linux_callback_count_libraries( struct dl_phdr_info * info, size_t size, void * data )
{
 if( data == NULL )
     return osapi_proc_error_params;

 if( strlen( info->dlpi_name ) > 0 )
     (*(t_size *) data)++;

 return 0;
}


static int linux_callback_get_libraries( struct dl_phdr_info * info, size_t size, void * data )
{
 t_dldata *	p_dldata;
 char 		str[ PATH_MAX ];
 char * 	libname			= NULL;
 char * 	ptr 			= NULL;

 if( data == NULL )     return osapi_proc_error_params;

 p_dldata = (t_dldata *) data;

 if( strlen( info->dlpi_name ) > 0 && p_dldata->curlibs < p_dldata->maxlibs )
   {
     strncpy( str, info->dlpi_name, PATH_MAX - 1 );

     // Get the Library name
     libname = basename( str );
     strncpy( str, libname, PATH_MAX - 1 );
     str[ PATH_MAX - 1 ] = '\0';

     if( strlen( str ) > 0 )
       {
	 strncpy( (*p_dldata->info)[ p_dldata->curlibs ].name, str, OSAPI_PROC_LIBRARY_MAX_NAME - 1 );
	 ((*p_dldata->info)[ p_dldata->curlibs ]).name[ OSAPI_PROC_LIBRARY_MAX_NAME ] = '\0';

	 // Find the version information
	 ptr = strstr( str, ".so." );
	 if( ptr != NULL )
	     ptr += 4;
	 else
	   {	// Check if library is in format: libname.[0-9]*
	     ptr = rindex( str, '.' );
	     if( ptr != NULL )  ptr++;
	   }

	 if( ptr == NULL )
	   (*p_dldata->info)[ p_dldata->curlibs ].version = 0;
	 else
	   {
	     errno = 0;
	     (*p_dldata->info)[ p_dldata->curlibs ].version = (unsigned int) atoi( ptr );
	     if( errno != 0 )
		 (*p_dldata->info)[ p_dldata->curlibs ].version = 0;

	     p_dldata->curlibs++;
	   }
       }
   }

 return 0;
}


static int linux_callback_get_library( struct dl_phdr_info * info, size_t size, void * data )
{
 struct library_release_data *	p_data;
 char 				str[ PATH_MAX + 1 ];
 char * 			libname			= NULL;
 char 		*		ptr 			= NULL;

 if( data == NULL ) return osapi_proc_error_params;

 p_data = (struct library_release_data *) data;

 if( strlen( info->dlpi_name ) > 0 && strcasecmp( info->dlpi_name, p_data->libname ) == 0 )
   {
     strncpy( str, info->dlpi_name, PATH_MAX );

     // Get the Library name
     libname = basename( str );
     strncpy( str, libname, PATH_MAX );

     ptr = strstr( str, ".so." );
     if( ptr != NULL )
       {
	 errno = 0;
	 if( strncpy( p_data->release, ptr+4, p_data->size ) != NULL )
	     return -1;		// Found and all ok
	 else
	     // Found but there was an error retrieving the Release information (both osapi_proc_error_params and errno are positive error codes)
	     return errno;
       }
   }

 return 0;	// Proceed to the next
}



t_status getNumberOfLoadedLibraries( t_size * p_maxlibs	)
{
 t_status st;

 status_reset( &st );

 if( p_maxlibs == (t_size *) 0 )
     status_iset( OSAPI_MODULE_PROC, __func__, osapi_proc_error_params, &st );
 else
   {
     *p_maxlibs = 0;
     int rc = dl_iterate_phdr( linux_callback_count_libraries, p_maxlibs );
     status_iset( OSAPI_MODULE_PROC, __func__, rc, &st );
   }

 return st;
}


t_status getListOfLoadedLibraries( t_size maxlibs, t_libinfo (*p_info)[] )
{
 t_status st;
 t_dldata data;

 status_reset( &st );

 if( (void *) p_info == NULL )
     status_iset( OSAPI_MODULE_PROC, __func__, osapi_proc_error_params, &st );
 else
   {
     // Set up wrapper structure to pass/receive information from the callback function
     data.maxlibs	= maxlibs;
     data.curlibs	= 0;
     data.info		= p_info;

     int rc = dl_iterate_phdr( linux_callback_get_libraries, (void *) &data );
     status_iset( OSAPI_MODULE_PROC, __func__, rc, &st );
   }

 return st;
}




t_status getLibraryRelease( const t_char * p_name, t_size max, char * p_release )
{
 t_status st;

 status_reset( &st );

 if( (void *) p_name == NULL || max < 1 || (void *) p_release == NULL )
     status_iset( OSAPI_MODULE_PROC, __func__, osapi_proc_error_params, &st );
 else
   {
     struct library_release_data data;

     // Copy the input into a wrapper structure for the syscall dl_iterate_phdr
     data.libname 	= p_name;
     data.size		= max;
     data.release	= p_release;

     int rc = dl_iterate_phdr( linux_callback_get_library, (void *) &data );

     if( rc > 0 )	// An error occurred
	 status_iset( OSAPI_MODULE_PROC, __func__, rc, &st );
   }

 return st;
}



#endif	// End of OS Linux
