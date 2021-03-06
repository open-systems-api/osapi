// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Status module entry point implementation file
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Force baseline before system headers
#include "general/general_baseline.h"

// System headers
#include <stdio.h>
#include <string.h>
#include <threads.h>

// // Generic OSAPI includes
#include "general/general.h"
#include "error/error.h"

// Include own headers
#include "status/status.h"
#include "status/status_platform.h"
#include "status/status_defs.h"

// *****************************************************************************************
//
// Section: Local declarations/definitions
//
// *****************************************************************************************

thread_local	static char	osapi_status_string[ OSAPI_STATUS_STRING_SIZE ];


// *****************************************************************************************
//
// Section: Function declarations (private)
//
// *****************************************************************************************

void 		status_message_iPrint		( t_status						);
void 		status_message_sPrint		( t_status						);
void		status_message_iGet			( t_status, t_size, t_char * 	);
void		status_message_sGet			( t_status, t_size, t_char * 	);


// *****************************************************************************************
//
// Section: Private Function definition
//
// *****************************************************************************************

void status_message_iPrint( t_status status )
{
  printf( "Module %s, function %s with status: %s.\n",
	  osapi_module_get( status.module ),
	  status.funcname,
	  error_string_get( status.module, status.code ) );
}

void status_message_sPrint( t_status status )
{
  printf( "V%s: Module %s, function %s with status: %s.\n", osapi_get_version_string(),
		  osapi_module_get( status.module ),
		  status.funcname,
		  status.string );
}

void status_message_iGet( t_status status, t_size size, t_char * p_message )
{
  if( p_message != OSAPI_NULL_CHAR_POINTER && size > 0 )
      snprintf( p_message, size, "V%s: Module %s, function %s with status: %s.",
    		  	  osapi_get_version_string(),
			  	  osapi_module_get( status.module ),
			  	  status.funcname,
			  	  error_string_get( status.module, status.code )
	      	  );
}

void status_message_sGet( t_status status, t_size size, t_char * p_message )
{
  if( p_message != OSAPI_NULL_CHAR_POINTER && size > 0 )
      snprintf( p_message, size, "V%s: Module %s, function %s with status: %s.",
    		  	  osapi_get_version_string(),
				  osapi_module_get( status.module ),
				  status.funcname,
				  status.string
	      	  );
}




// *****************************************************************************************
//
// Section: Private Function definition
//
// *****************************************************************************************


void status_instance_clear( t_status * p_status )
{
  p_status->module		=	OSAPI_MODULE_NONE;
  p_status->type 		= 	osapi_status_library_osapi;
  p_status->code 		= 	0;
  p_status->funcname	=	OSAPI_EMPTY_STRING;
}

void status_instance_set( t_module module, t_status_type type, t_status_funcname fname, t_error code, t_status * p_status )
{
  p_status->module		= (Byte) module;
  p_status->type		= type;
  p_status->code		= code;
  p_status->funcname	= fname;
}

void status_instance_setString( t_module module, t_status_type type, t_status_funcname fname, t_status_string statusString, t_status * p_status )
{
  p_status->module		= (Byte) module;
  p_status->type		= type;
  p_status->funcname	= fname;

  // Copy the string to the thread local storage and assign the status string pointer to it
  strncpy( osapi_status_string, statusString, OSAPI_STATUS_STRING_SIZE );
  osapi_status_string[ OSAPI_STATUS_STRING_SIZE -1 ] = '\0';		// Enforce the null termination
  p_status->string	= osapi_status_string;
}

void status_message_print( t_status status )
{
  if( status_success( status ) )
	  status_instance_clear  ( &status  );

  // Search the library type that produce the status information
  switch( status.type )
	{
	  case	osapi_status_library_osapi: 	status_message_iPrint( status );	break;
	  case	osapi_status_library_c:	 		status_message_cPrint( status );	break;
	  case	osapi_status_library_loader:	status_message_sPrint( status );	break;
	  default:		 						break;		// Do nothing
	}
}

void status_message_retrieve( t_status status, t_size size, t_char * p_message )
{
  if( status_success( status ) )
	  status_instance_clear( &status  );

  // Search the library type that produce the status information
  switch( status.type )
	{
	  case	osapi_status_library_osapi: 	status_message_iGet( status, size, p_message );	break;
	  case	osapi_status_library_c:	 		status_message_cGet( status, size, p_message );	break;
	  case	osapi_status_library_loader:	status_message_sGet( status, size, p_message );	break;
	  default:		 						break;		// Do nothing
	}
}

const char * status_module_get( t_status status )
{
  if( status_success( status ) )
	  status_instance_clear( &status  );

  return osapi_module_get( status.module );
}

const char * status_function_get( t_status status )
{
  if( status_success( status ) )
	  status_instance_clear( &status  );

  return status.funcname;
}

const char * status_message_get( t_status status )
{
  if( status_success( status ) )
	  status_instance_clear( &status  );

  // Search the library type that produce the status information
  switch( status.type )
	{
	  case	osapi_status_library_osapi: 	return error_string_get( status.module, status.code );
	  case	osapi_status_library_c:	 		return status_error_getSystem( status.code );
	  case	osapi_status_library_loader:	return osapi_status_string;
	  default:		 						return OSAPI_EMPTY_STRING;
	}

}


void osapi_status_trace( const char * func, uint64_t line, t_status st )
{
  if( st.code == 0 )	osapi_trace( func, " (", line, "%s", ") - Leaving" 				  );
  else			  		osapi_trace( func, " (", line, ") - Leaving with: %s", status_message_get( st ) );
}


bool status_success_is( t_status status )
{
  return status_success( status );
}

