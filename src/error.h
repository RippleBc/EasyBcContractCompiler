#define ERROR_SUCCESS

int errorCount = 0;
int warnCount= 0;
int lineNo;

void printResult(char *fname);
int errOccur();
void internalError(char *info);
void parseError(char *info, char *name);
void lexError(char *info);
void yyerror(char *info);