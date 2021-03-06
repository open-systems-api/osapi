// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Filesystem module implementation for file elements
//
// *****************************************************************************************


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Generic OSAPI includes
#include "general/general.h"
#include "general/general_protocol.h"
#include "error/modules/error_fs.h"
#include "status/status.h"

// Own declarations
#include "fs/fs_element.h"
#include "fs/fs_file.h"
#include "fs/fs_helper.h"

// *****************************************************************************************
//
// Section: Function definition
//
// *****************************************************************************************


t_status fs_file_setPositionBegin( const t_file * p_file )
{
  return fs_file_setPosition( p_file, osapi_fs_file_position_begin, (t_offset) 0 );
}


t_status fs_file_setPositionEnd( const t_file * p_file )
{
  return fs_file_setPosition( p_file, osapi_fs_file_position_end, (t_offset) 0 );
}


t_status fs_file_setPositionAt( const t_file * p_file, t_offset offset )
{
  return fs_file_setPosition( p_file, osapi_fs_file_position_set, offset );
}


t_status fs_file_setBlockSize	( t_file * p_file, t_size size )
{
  t_status		st;

  status_reset( &st );

  if( p_file == NULL || size == 0 )
    { status_iset( OSAPI_MODULE_FS, __func__, osapi_fs_error_params, &st ); return st; }

  p_file->file.block_size = size;

  return st;
}
