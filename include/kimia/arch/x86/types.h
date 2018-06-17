/**
 * Kimia OS
 * All typedef changes is here.
 */

#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned char *		String; 
//----------------------------------------
//typedef for x86(32 bits) platforms
typedef unsigned int		uint32;
typedef signed int			int32;
typedef unsigned short		uint16;
typedef signed short		int16;
typedef unsigned char		uint8;
typedef signed char			int8;
typedef unsigned long long  long_int;
typedef long double			long_max;
typedef unsigned char       Boolean;
typedef unsigned int        size_t;
//----------------------------------------
#define true		1
#define false		0
#define STR         (String)



#endif /*_TYPES_H*/
