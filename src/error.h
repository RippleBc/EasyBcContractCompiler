#ifndef _ERROR_H_0676265892738329346263904720570350275_
#define _ERROR_H_0676265892738329346263904720570350275_

#define ERROR_SUCCESS			(0)
#define ERROR_UNDECLARE			(-1)

void print_result(char *fname);
int err_occur();
void internal_error(char *info);
void parse_error(char *info, char *name);
void lex_error(char *info);
void yyerror(char *info);

#endif

