/**
 * System independent configuration.
 */

#ifndef __CONFIG_H_2007223627632636296362936424723070235_
#define __CONFIG_H_2007223627632636296362936424723070235_


typedef struct
{
    char *target_name;
}
Xinterface;

#define GENERATE_AST		(1) 

#define DAG_DEBUG			(2)
#define CONST_FOLDING_DEBUG	(4)
#define COMMON_EXPR_DEBUG	(8)
#define SYSTEM_CALL_DEBUG	(16)

/*
#define DEBUG				(DAG_DEBUG | CONST_FOLDING_DEBUG | \
								COMMON_EXPR_DEBUG | SYSTEM_CALL_DEBUG)
*/
#define DEBUG				(0)

#ifdef __linux__
#define HAVE_SNPRINTF	1
#define HAVE_VSNPRINTF	1
#define HAVE_STRCASECMP	1
#endif

#endif

