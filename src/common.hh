typedef struct 
{
	char name[NAME_LEN];
	int key; // token type
	int attr;
	int ret_type;
	int arg_type;
} KEYENTRY;

KEYENTRY Keytable[] = {
	{"abs", SYS_FUNCT, fABS, TYPE-INTEGER, TYPE-INTEGER},
	{"and", kAND, KEYWORD, 0, 0},
	{"array", kARRAY, KEYWORD, 0, 0},
	{"begin", kBEGIN, KEYWORD, 0, 0},
	{"boolean", SYS-TYPE, tBOOLEAN, 0, 0},
	{"case", kCASE, KEYWORD, 0, 0},
	{"char", SYS-TYPE, tCHAR, 0, 0},
	{"chr", SYS-TYPE, tCHAR, 0, 0},
	{"const", kCONST, KEYWORD, 0, 0},
	{"div", kDIV, KEYWORD, 0, 0},
	{"do", kDO, KEYWORD, 0, 0}
}

struct {
	char *name;
	int key;
} key-to-name[] = {
	{"SYS-FUNCT", SYS-FUNCT},
	{"kAND", kAND},
	{"kARRAY", kRRAY}
}