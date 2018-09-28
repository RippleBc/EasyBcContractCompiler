struct node
{
	short op;
	char *opName;
	short count;
	Symbol syms[3];
	Symtab symtab;
	union {
		int
		struct
		{
			Symbol label;
			int trueOrFalse;
		}
	}
	Type type;
	struct node* kids[2];
	struct node* link;
}