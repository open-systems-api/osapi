// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Net(work) private error declarations
//
// *****************************************************************************************

#ifndef OSAPI_ERROR_PRIV_NET_H_
#define OSAPI_ERROR_PRIV_NET_H_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include own error public declarations
#include "error/modules/error_net.h"

// *****************************************************************************************
//
// Section: Clock Error Definitions
//
// *****************************************************************************************

#define error_net_X(a, b, c) [a]=c,

static const char * net_errors[] =
{
  #include "error/mappings/table_net.h"
};

#undef error_net_X

#endif /* OSAPI_ERROR_PRIV_NET_H_ */
