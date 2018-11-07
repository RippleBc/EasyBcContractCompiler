#include "../common.h"
#include "../parser/rule.h"

static int folding_const = 0;

/*  */
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
        case TYPE_CHAR: \
                con->v.c = (n->kids[0]->syms[0]->v.c) realop (n->kids[1]->syms[0]->v.c); \
                break; \
        case TYPE_REAL: \
                con->v.f = (n->kids[0]->syms[0]->v.f) realop (n->kids[1]->syms[0]->v.f); \
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

void const_folding(Node n)
{
    Symbol con;
    char little_buf[NAME_LEN];

    if ((generic(n->kids[0]->op) == CNST) && 
        ((n->kids[1] == NULL) || (generic(n->kids[1]->op) == CNST)))
    {
        /*  */
        if ((n->kids[0]->syms[0]->type->type_id == TYPE_STRING) || 
            ((n->kids[1] != NULL) && (n->kids[1]->syms[0]->type->type_id == TYPE_STRING)))
        {
            return;
        }

        /*  */
        snprintf(little_buf, sizeof(little_buf) - 1, "g_con_%d", folding_const++);
        con = new_symbol(little_buf, DEF_CONST, n->kids[0]->syms[0]->type->type_id);
        n->syms[0] = con;

        switch(generic(n->op))
        {
        binary_xx(BAND, &);
        binary_xx(BOR, |);
        binary_xx(BXOR, ^);
        binary_xx(MOD, %);
        binary_xx(RSH, >>);
        binary_xx(LSH, <<);
        real_binary_xx(AND, &&);
        real_binary_xx(OR, ||);
        real_binary_xx(EQ, ==);
        real_binary_xx(NE, !=);
        real_binary_xx(GT, >);
        real_binary_xx(GE, >=);
        real_binary_xx(LT, <);
        real_binary_xx(LE, <=);
        real_binary_xx(ADD, +);
        real_binary_xx(SUB, -);
        real_binary_xx(DIV, /);
        real_binary_xx(MUL, *);
        single_xx(NOT, !);
        single_xx(BCOM, ~);
        single_xx(CVF, (float));
        single_xx(CVI, (int));
        real_single_xx(NEG, -);
        default:
            assert(0);
            break;

        }
        
#if DEBUG & CONST_FOLDING_DEBUG
        printf("Const folded to %p(%d). left %d, right %d\n", n, n->syms[0]->v.i, n->kids[0]->syms[0]->v.i, 
            n->kids[1] == NULL ? -1 : n->kids[1]->syms[0]->v.i);
#endif

        /*  */
        n->kids[0] = n->kids[1] = NULL;
        n->op = CNST;
    }
}
