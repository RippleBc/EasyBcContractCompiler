/* 显示错误信息，当编译器发现错误时，就调用该函数在指定设备（显示设备或者磁盘文件）上显示错误信息。
 该函数包含两个参数info和name分别表示错误信息以及错误名 */
void parseError(char *info, char *name)
{
	fprintf(errfp, "\nError at line %d: \n", lineNo);
	fprintf(errfp, "%s\n", lineBuf);
	printfPos(errfp);

	fprintf(strerr, "\nError at line %d: \n", lineNo);
	fprintf(strerr, "%s\n", lineBuf);
	printPos(strerr);

	if(*name)
	{
		fprintf(errfp, ": %s  %s", info, name);
		fprintf(strerr, ": %s  %s", info, name);
		snprintf(ebuf[errorCount++], sizeof(ebuf[errorCount++]) - 1, "\nError(%d): %s '%s'", lineNo, info, name);
	}
	else 
	{
		fprintf(errfp, ": %s \n", info);
		fprintf(strerr, ": %s \n", info);
		snprintf(ebuf[errorCount++], sizeof(ebuf[errorCount++]) - 1, "\nError(%d): %s \n", lineNo, info);
	}

	if(errorCount >= MAX_ERR)
	{
		clear();
		printResult(pasname);
		exit(1);
	}
}

/* 显示编译器内部错误，比如在进行语法分析时内部堆栈溢出 */
void internalError(char *info)
{
	sprintf(ebuf[errorCount++], "Internal Error %s\n", info);
	fprintf(errfp, "Internal Error (%d): %s \n", lineNo, info);

	if(errorCount >= MAX_ERR)
	{
		clear();
		printResult(pasname);
		exit(0);
	}
}

/* 显示词法分析错误，yyerror则由语法分析器调用，
 这两个函数内部都调用了函数parseError */
void lexError(char *info)
{
	fprintf(errfp, "\nError at line %d: \n", lineNo);
	fprintf(errfp, "%s \n", lineBuf);
	printPos(errfp);

	fprintf(stderr, "\nError at line %d: \n", lineNo);
	fprintf(stderr, "%s \n", lineBuf);
	printPos(stderr);

	sprintf(ebuf[errorCount++], sizeof(ebuf[errorCount++]) - 1, ": %s", info);

	fprintf(errfp, "\nError （%d): %s", lineNo, info);
	fprintf(stderr, "\nError (%d): %s", lineNo, info);
}

void yyerror(char *info)
{
	parseError(info, "");
}

void printResult(char *fname)
{
	printf("\n%s: %d lines, %d errors.\n", fname, lineNo, errorCount);

	if(!errorCount)
	{
		print("OK! \n\n");
	}
}

int errOccur()
{
	return errorCount;
}