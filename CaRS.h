#pragma once
#ifndef cabecalho
#define cabecalho

//#include "C:\Program Files\IBM\ILOG\CPLEX_Studio_Community2212\opl\include\ilcplex\cplex.h"
#include "C:\Program Files\IBM\ILOG\CPLEX_Studio2211\opl\include\ilcplex\cplex.h"
#include "C:\gurobi1300\win64\include\gurobi_c++.h"


#define MAX_CID 20
#define MAX_CAR	10
#define MAX_NOME 200

char nomeInstancia[MAX_NOME];
int num_cidades;
int num_carros;
int mat_distancia[MAX_CAR][MAX_CID][MAX_CID];
int mat_retorno[MAX_CAR][MAX_CID][MAX_CID];

void leArquivoNaoEuclideano(const char* caminho);
void imprimeArquivoNaoEuclideano(const char * arq);
void escreveCEPLEX(const char* arq);

void optimize_cplex(const char* modelo, const char* instancia, const char* arq_solucao, const char* arq_res_obtidos);
void status_cplex(CPXENVptr env, int sts, const char* function_name);

void escreve_solucao(const char* arq_solucao, double valor_obj, int num_vars, double* var_values, char** var_names);

void optimize_gurobi(const char* modelo, const char* arq_solucao, const char* arq_res_obtidos);
void status_gurobi(GRBenv* env, int error, const char* function_name);

#endif // cabecalho
