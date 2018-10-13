// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide Status module macros & other definitions
//
// *****************************************************************************************

#ifndef STATUS_STATUS_DEFS_H_
#define STATUS_STATUS_DEFS_H_

// *****************************************************************************************
//
// Section: Constants/Macros for client applications
//
// *****************************************************************************************

#define	OSAPI_STATUS_STRING_SIZE	101

// Helper definitions for a correct way to check for success/failure of operations
#define status_success( x )	( x.code == 0 && x.type == e_library_osapi	)
#define status_failure( x )	( x.code != 0 || x.type != e_library_osapi	)

#define status_error( x )	status_failure( x )
#define status_true(  x )	( status_failure( x ) ? 0 : 1 )
#define status_false( x )	( status_success( x ) ? 1 : 0 )

// Expansion of structure arguments (this avoids that client applications need to know internal details of t_status)
#define OSAPI_STATUS(x)		status(x.code,x.module,x.type,x.funcname)


// *****************************************************************************************
//
// Section: Macros/definitions for internal usage
//
// *****************************************************************************************

// Status information, internal or external
//#define STATUS_INTERNAL		0
//#define STATUS_SYSTEM		1

enum osapi_library_id
{
  e_library_osapi 		= 0,

  // System Libraries get negative codes
  e_library_c			= -1,
  e_library_loader		= -2,
};

// Short notation for a success status
#define RETURN_STATUS_SUCCESS	{ t_status st; status_reset( &st ); return st; }

// Support macros for setting internal/external status errors

#define status_iset(m,f,e,r) 		status_set( m, e_library_osapi, f, e, r )
#define status_eset(m,f,e,r) 		status_set( m, e_library_c,     f, e, r )


#endif /* STATUS_STATUS_DEFS_H_ */
