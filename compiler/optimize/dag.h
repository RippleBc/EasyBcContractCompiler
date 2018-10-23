#ifndef _DAG_H_
#define _DAG_H_

void print_dags(List dags);
/* 将AST森林转化为DAG森林 */
int gen_dag(List ast_forest, List dag_forest);
int emit_code(List dags);

#endif

