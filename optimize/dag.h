#ifndef _DAG_H_
#define _DAG_H_

void print_dags(List dags);
int gen_dag(List ast_forest, List dag_forest);
int emit_code(List dags);

#endif

