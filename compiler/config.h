/**
 * System independent configuration.
 */

#ifndef __CONFIG_H_
#define __CONFIG_H_


typedef struct
{
    char *target_name;
}
Xinterface;

#define DAG_DEBUG			(2)
#define CONST_FOLDING_DEBUG	(4)
#define COMMON_EXPR_DEBUG	(8)
#define SYSTEM_CALL_DEBUG	(16)

/*
#define DEBUG				(DAG_DEBUG | CONST_FOLDING_DEBUG | \
								COMMON_EXPR_DEBUG | SYSTEM_CALL_DEBUG)
*/
#define DEBUG				(0)

#endif

