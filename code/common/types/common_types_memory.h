// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Common declarations for a generic buffer type
//
// *****************************************************************************************

#ifndef OSAPI_COMMON_TYPES_MEMORY_H_
#define OSAPI_COMMON_TYPES_MEMORY_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import OSAPI headers
#include "general/general_types.h"

// *****************************************************************************************
//
// Section: Type definitions
//
// *****************************************************************************************

/// Structure supporting a self describing memory/buffer
/// The reasoning is that naked memory handling is more error prone and encapsulation of
/// memory supported by a "buffer" type can provided more robust code.
struct osapi_common_memory_S
{
  t_size	capacity;		///< The memory allocated capacity
  Byte		canary;			///< A MAGIC constant to indicate if the data pointer is really pointing to a previously allocated memory
  Byte		type;			///< The type of memory that was initially requested. A value of 0 means that memory can grow (malloc).
  void	  *	data;			///< Allocated HEAP memory location
};

typedef struct osapi_common_memory_S	t_memory;


#endif /* OSAPI_COMMON_TYPES_MEMORY_H_ */
