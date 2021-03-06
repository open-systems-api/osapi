// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	String wide encoding implementation file
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Force baseline before system headers
#include "general/general_baseline.h"

// System includes
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <strings.h>
#include <wchar.h>
#include <stdbool.h>

// Generic OSAPI includes
#include "general/general.h"
#include "status/status.h"

// Own declarations
#include "string/string_wide.h"
#include "error/modules/error_string.h"

// *****************************************************************************************
//
// Section: Function definition
//
// *****************************************************************************************


t_status string_wide_new( t_size size, t_wString * p_string )
{
  t_status	st;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER || size == 0 )
      status_iset( OSAPI_MODULE_STRING,__func__, osapi_string_error_params, &st );
  else
    {
      errno = 0;
      // Always request 1 byte extra to ensure that the '\0' ends the array of chars
      p_string->ps_location = (wchar_t *) calloc(1, size + 1 );

      if( p_string->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
      else
	{
	  p_string->tsize = size;	// Don't count the null char
	  p_string->csize = 0;		// Only space is allocated
	}
    }

  return st;
}

t_status string_wide_delete( t_wString * p_string )
{
  t_status	st;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      p_string->tsize = 0;
      p_string->csize = 0;

      if( p_string->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
      else
	  free( (void *) p_string->ps_location );
    }

  return st;
}

t_status string_wide_create( const wchar_t * p_initial_string, t_wString * p_string )
{
  t_status	st;
  t_size	len;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER || p_initial_string == OSAPI_WIDE_CHAR_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      len = (t_size) wcslen( p_initial_string );

      errno = 0;
      // Always request 1 byte extra to ensure that the '\0' ends the array of chars
      p_string->ps_location = (wchar_t *) calloc(1, len + 1 );

      if( p_string->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
      else
	{
	  if( wcscpy( p_string->ps_location, p_initial_string ) != OSAPI_WIDE_CHAR_NULL_POINTER )
	      p_string->tsize = p_string->csize = len;
	  else
	    {
	      // Unable to copy string, release memory
	      string_wide_delete( p_string );
	      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_create, &st );
	    }
	}
    }

  return st;
}

t_status string_wide_clone( t_wString * ps_old, t_wString * ps_new )
{
  t_status	st;

  status_reset( & st );

  if( ps_old == OSAPI_WIDE_STRING_NULL_POINTER || ps_new == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      // Make sure that new string is not already bounded to some heap address
      if( ps_new->ps_location != OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_exists, &st );
      else
	  st = string_wide_create( ps_old->ps_location, ps_new );
    }

  return st;
}

t_status string_wide_put( const wchar_t * message, t_wString * p_string )
{
  t_status	st;
  t_size	len;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      if( p_string->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
      else
	{
	  if( p_string->csize > 0 )
	      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_exists, &st );
	  else
	    {
	      len = (t_size) wcslen( message );
	      if( p_string->tsize < len )
		  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_noSpace, &st );
	      else
		{
		  errno = 0;
		  if( wcsncpy( p_string->ps_location, message, (size_t) len ) == OSAPI_WIDE_CHAR_NULL_POINTER )
		      status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
		}
	    }
	}
    }

  return st;
}

t_status string_wide_set( const wchar_t * message, t_wString * p_string )
{
  t_status	st;
  t_size	len;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      if( p_string->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
      else
	{
	  len = (t_size) wcslen( message );
	  if( len > p_string->tsize )
	      // Limit the size of the copied string
	      len = p_string->tsize;

	  errno = 0;
	  if( wcsncpy( p_string->ps_location, message, (size_t) len ) == OSAPI_WIDE_CHAR_NULL_POINTER )
	      status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
	}
    }

  return st;
}

t_status string_wide_size( t_wString * p_string, t_size * p_size )
{
  t_status	st;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
      *p_size = p_string->csize;

  return st;
}

t_status string_wide_print( t_wString * p_string )
{
  t_status	st;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
      wprintf(L"%.*s\n", (int) p_string->csize, p_string->ps_location );

  return st;
}

t_status string_wide_get( t_wString * p_string, t_size maxSize, wchar_t * message )
{
  t_status	st;

  status_reset( & st );

  if( p_string == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      errno = 0;
      if( wcsncpy( message, p_string->ps_location, (size_t) maxSize ) == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
    }

  return st;
}

t_status string_wide_concat( t_wString * ps_str1, t_wString * ps_str2, t_wString * ps_final )
{
  t_status	st;

  status_reset( & st );

  if( ps_final == OSAPI_WIDE_STRING_NULL_POINTER || ps_str1 == OSAPI_WIDE_STRING_NULL_POINTER || ps_str2 == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      if( ps_final->ps_location == ps_str1->ps_location || ps_final->ps_location == ps_str2->ps_location )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_sameString, &st );		// One of the string is the same as the destination string
      else
	{
	  string_wide_delete( ps_final );		  // Make sure to release memory of current string

	  // Allocate memory to hold both strings + '\0'
	  ps_final->ps_location = calloc( 1, ps_str1->csize + ps_str2->csize + 1 );

	  if( ps_final->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
	  else
	    {
	      ps_final->tsize = ps_str1->csize + ps_str2->csize;

	      errno = 0;
	      if( wcsncpy( ps_final->ps_location, ps_str1->ps_location, (size_t) ps_str1->csize ) == OSAPI_WIDE_CHAR_NULL_POINTER )
		  status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
	      else
		{
		  errno = 0;
		  if( wcsncpy( ps_final->ps_location, ps_str1->ps_location, (size_t) ps_str1->csize ) == OSAPI_WIDE_CHAR_NULL_POINTER )
		      status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
		  else
		      ps_final->csize = (t_size) wcslen( ps_final->ps_location );
		}
	    }
	}
    }

  return st;
}

t_status string_wide_compare( t_wString * ps_str1, t_wString * ps_str2, Byte * p_result )
{
  t_status	st;

  status_reset( & st );

  if( ps_str1 == OSAPI_WIDE_STRING_NULL_POINTER || ps_str2 == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      if( ps_str1->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER || ps_str1->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
      else
	  *p_result = (Byte) wcscmp( ps_str1->ps_location, ps_str2->ps_location );
    }

  return st;
}

t_status string_wide_equal( t_wString * ps_str1, t_wString * ps_str2, bool * p_result )
{
  t_status	st;

  status_reset( & st );
  *p_result = 0;	// Assume FALSE

  if( ps_str1 == OSAPI_WIDE_STRING_NULL_POINTER || ps_str2 == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      // Strings must have equal size in the first place
      if( ps_str1->csize == ps_str2->csize )
	{
	  errno = 0;
	  if( wcsncmp( ps_str1->ps_location, ps_str2->ps_location, (size_t) ps_str1->csize ) == 0 )
	      *p_result = 0;
	  else
	      status_eset( OSAPI_MODULE_STRING, __func__, errno, &st );
	}
    }

  return st;
}

/*
t_status string_wide_compareIcase( t_wString * ps_str1, t_wString * ps_str2, Byte * p_result )
{
  t_status	st;

  status_reset( & st );

  if( ps_str1 == OSAPI_WIDE_STRING_NULL_POINTER || ps_str2 == OSAPI_WIDE_STRING_NULL_POINTER )
      status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_params, &st );
  else
    {
      if( ps_str1->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER || ps_str1->ps_location == OSAPI_WIDE_CHAR_NULL_POINTER )
	  status_iset( OSAPI_MODULE_STRING, __func__, osapi_string_error_nullPointer, &st );
      else
	  *p_result = (Byte) strcasecmp( ps_str1->ps_location, ps_str2->ps_location );
    }

  return st;
}

*/



