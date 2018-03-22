/*
 * error_string.h
 *
 *  Created on: 03/05/2017
 *      Author: joao
 */

#ifndef CODE_ERR_ERROR_STRING_H_
#define CODE_ERR_ERROR_STRING_H_

// Include General error definitions
#include <error/error_def.h>

// Define STRING module private errors

#define error_string_X(a, b, c) a b,
enum string_X {
	  #include <error/table_string.h>
};
#undef error_string_X


#endif /* CODE_ERR_ERROR_STRING_H_ */
