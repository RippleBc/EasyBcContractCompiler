#include "../common.h"

#define binary_xx(optype, realop) case optype: \
switch(con->kids[0]->type->type_id) { \
        case TYPE_INTEGER: \
                con->val.i = (con->kids[0]->val.i) realop (con->kids[1]->val.i); \
                break; \
        case TYPE_BOOLEAN: \
                con->val.b = (con->kids[0]->val.b) realop (con->kids[1]->val.b); \
                break; \
        case TYPE_CHAR: \
                con->val.c = (con->kids[0]->val.c) realop (con->kids[1]->val.c); \
                break; \
        default: \
                break; \
} \
break;

#define real_binary_xx(optype, realop) case optype: \
switch(con->kids[0]->type->type_id) { \
        case TYPE_INTEGER: \
                con->val.i = (con->kids[0]->val.i) realop (con->kids[1]->val.i); \
                break; \
        case TYPE_BOOLEAN: \
                con->val.b = (con->kids[0]->val.b) realop (con->kids[1]->val.b); \
                break; \
        case TYPE_CHAR: \
                con->val.c = (con->kids[0]->val.c) realop (con->kids[1]->val.c); \
                break; \
        case TYPE_REAL: \
                con->val.f = (con->kids[0]->val.f) realop (con->kids[1]->val.f); \
                break; \
        default: \
                break; \
} \
break;

#define single_xx(optype, realop) case optype: \
switch(con->kids[0]->type->type_id) { \
        case TYPE_INTEGER: \
                con->val.i = realop (con->kids[0]->val.i); \
                break; \
        case TYPE_BOOLEAN: \
                con->val.b = realop (con->kids[0]->val.b); \
                break; \
        case TYPE_CHAR: \
                con->val.c = realop (con->kids[0]->val.c);\
                break; \
        default: \
                break; \
} \
break;

#define real_single_xx(optype, realop) case optype: \
switch(con->kids[0]->type->type_id) { \
        case TYPE_INTEGER: \
                con->val.i = realop (con->kids[0]->val.i); \
                break; \
        case TYPE_BOOLEAN: \
                con->val.b = realop (con->kids[0]->val.b); \
                break; \
        case TYPE_CHAR: \
                con->val.c = realop (con->kids[0]->val.c);\
                break; \
        case TYPE_REAL: \
                con->val.f = realop (con->kids[0]->val.f); \
                break; \
        default: \
                break; \
} \
break;

void arithmetical_operate(Node con)
{
  switch(con->op)
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
    single_xx(INCR, ++);
    single_xx(DECR, --);
    single_xx(CVF, (float));
    single_xx(CVI, (int));
    real_single_xx(NEG, -);
    default:
      assert(0);
      break;
  }
}

void assign_or_load_val(Value v, Symbol p)
{
  switch(p->type->type_id)
  {
    case TYPE_INTEGER:
    {
      v->i = p->v.i;
    }
    break;
    case TYPE_CHAR:
    {
      v->c = p->v.c;
    }
    break;
    case TYPE_BOOLEAN:
    {
      v->b = p->v.b;
    }
    break;
    case TYPE_REAL:
    {
      v->f = p->v.f;
    }
    break;
    case TYPE_STRING:
    {
      v->s = p->v.i;
    }
    break;
  }
}