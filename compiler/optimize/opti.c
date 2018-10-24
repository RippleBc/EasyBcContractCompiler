#include "../common.h"
#include "../parser/rule.h"

static int folding_const = 0;

void const_folding(Node n)
{
    Symbol con;
    char little_buf[NAME_LEN];

    if ((generic(n->kids[0]->op) == CNST) && ((n->kids[1] == NULL) || (generic(n->kids[1]->op) == CNST)))
    {
        /* do not folding strings. */
        if ((n->kids[0]->syms[0]->type->type_id == TYPE_STRING) || ((n->kids[1] != NULL) && (n->kids[1]->syms[0]->type->type_id == TYPE_STRING)))
            return;

        snprintf(little_buf, sizeof(little_buf) - 1, "g_con_%d", folding_const++);
        con = new_symbol(little_buf, DEF_CONST, n->kids[0]->syms[0]->type->type_id);
        n->syms[0] = con;

        switch(generic(n->op))
        {
            /*
            binary_xx(op,	realop)		singlar operator
            single_xx(op,  realop)		binary operator
            */
#define binary_xx(optype, realop) case optype: \
				switch(n->kids[0]->syms[0]->type->type_id) { \
						case TYPE_INTEGER: \
								con->v.i = (n->kids[0]->syms[0]->v.i) realop (n->kids[1]->syms[0]->v.i); \
								break; \
						case TYPE_BOOLEAN: \
								con->v.b = (n->kids[0]->syms[0]->v.b) realop (n->kids[1]->syms[0]->v.b); \
								break; \
						case TYPE_CHAR: \
								con->v.c = (n->kids[0]->syms[0]->v.c) realop (n->kids[1]->syms[0]->v.c); \
								break; \
						default: \
								break; \
				} \
				break;

#define real_binary_xx(optype, realop) case optype: \
				switch(n->kids[0]->syms[0]->type->type_id) { \
						case TYPE_INTEGER: \
								con->v.i = (n->kids[0]->syms[0]->v.i) realop (n->kids[1]->syms[0]->v.i); \
								break; \
						case TYPE_BOOLEAN: \
								con->v.b = (n->kids[0]->syms[0]->v.b) realop (n->kids[1]->syms[0]->v.b); \
								break; \
						case TYPE_REAL: \
								con->v.f = (n->kids[0]->syms[0]->v.f) realop (n->kids[1]->syms[0]->v.f); \
								break; \
						case TYPE_CHAR: \
								con->v.c = (n->kids[0]->syms[0]->v.c) realop (n->kids[1]->syms[0]->v.c); \
								break; \
						default: \
								break; \
				} \
				break;

#define single_xx(optype, realop) case optype: \
				switch(n->kids[0]->syms[0]->type->type_id) { \
						case TYPE_INTEGER: \
								con->v.i = realop (n->kids[0]->syms[0]->v.i); \
								break; \
						case TYPE_BOOLEAN: \
								con->v.b = realop (n->kids[0]->syms[0]->v.b); \
								break; \
						case TYPE_CHAR: \
								con->v.c = realop (n->kids[0]->syms[0]->v.c);\
								break; \
						default: \
								break; \
				} \
				break;

#define real_single_xx(optype, realop) case optype: \
				switch(n->kids[0]->syms[0]->type->type_id) { \
						case TYPE_INTEGER: \
								con->v.i = realop (n->kids[0]->syms[0]->v.i); \
								break; \
						case TYPE_BOOLEAN: \
								con->v.b = realop (n->kids[0]->syms[0]->v.b); \
								break; \
						case TYPE_REAL: \
								con->v.f = realop (n->kids[0]->syms[0]->v.f); \
								break; \
						case TYPE_CHAR: \
								con->v.c = realop (n->kids[0]->syms[0]->v.c);\
								break; \
						default: \
								break; \
				} \
				break;

            binary_xx(AND, &&);
            binary_xx(OR, ||);
            single_xx(NOT, !);
            single_xx(BCOM, !);
            real_single_xx(NEG, -);
            real_binary_xx(EQ, ==);
            real_binary_xx(NE, !=);
            real_binary_xx(GT, >);
            real_binary_xx(GE, >=);
            real_binary_xx(LT, <);
            real_binary_xx(LE, <=);
            binary_xx(BAND, &);
            binary_xx(BOR, |);
            real_binary_xx(ADD, +);
            real_binary_xx(SUB, -);
            real_binary_xx(DIV, /);
            real_binary_xx(MUL, *);
            binary_xx(MOD, %);
            binary_xx(RSH, >>);
            binary_xx(LSH, <<);
            single_xx(CVF, (float));
            single_xx(CVI, (int));
#undef single_xx
#undef real_single_xx
#undef binary_xx
#undef real_binary_xx
            /*
            			case AND:
            			case OR:
            			case NOT:
            			case BCOM:
            			case NEG:
            			case EQ:
            			case NE: 
            			case GT: 
            			case GE: 
            			case LE:
            			case LT:
            			case BOR: 
            			case BAND: 
            			case BXOR:
            			case ADD: 
            			case SUB:  
            			case RSH:
            			case LSH:
            			case DIV: 
            			case MUL:
            			case MOD:
            			case CVF: 
            			case CVI: 
            			case CVP:
            			case CVU:
            */
        default:
            assert(0);
            break;

        }
        /* prune left and right kids. */
        n->kids[0] = n->kids[1] = NULL;
        n->op = CNST;
#if DEBUG & CONST_FOLDING_DEBUG

        printf("Const folded to %p(%d).\n", n, n->syms[0]->v.i);
#endif

    }
}
