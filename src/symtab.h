union value
{
	char c;
	char *s;
	int i;
	float f;
	boolean b;
	long l;
	unsigned long u;
	long double d;
	void *p;
	void (*g)(void);
}

typedef struct symbol
{
	char name[NAME-LEN];
	char rname[LABEL-LEN];
	/* 标识符的属性值（PROG，FUNCT，PROC之一） */
	int defn;
	int offset;
	value v;
	struct symbol *next;
	struct symbol *lchild, rchild;
	struct symbolHead *tab;
	/* type和type-link相结合用来表达一个标识符的类型特征，
	 当type表示一个基本类型时，就不必查找type-link了；
	 如果type表示一个用户自定义类型时，通过type-link查找相关类型的信息 */
	Type type;
	struct type *typeLink;
} symbol;

/* 类型标识表的表项，记录了类型的所有信息 */
typedef struct type
{
	char name[NAME-LEN];
	int typeId;
	int numEle;
	int size;
	int align;
	/* 对于枚举和记录，枚举中的所有元素或者记录中的所有域按照申明顺序组成symbol链表，
	 first和last分别指向链首和链尾。对于数组类型，first指向下标类型的第一个元素，
	 last指向一个虚符号，而这个虚符号的类型就是元素类型。 */
	symbol *first;
	symbol *last;
	struct type *next;
} type;

/* 符号表表头 */
typedef struct symbolHead
{
	char name[NAME-LEN];
	char rname[LABEL-LEN];
	int id;
	int level;
	int defn;
	/* 过程或函数的返回类型 */
	Type type;
	/* 局部变量的总字节数 */
	int localSize;
	/* 参数的总字节数 */
	int argsSize;
	/* 参数链表 */
	symbol *args;
	/* 变量链表 */
	symbol *locals;
	/* 局部符号表（参数和变量），二叉树的根 */
	symbol *localtab;
	/*过程或函数返回值的类型链接 */
	type *type-link;
	/* 链接上一层符号表 */
	struct symbolHead *parent;
} symtab;