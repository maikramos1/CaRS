#pragma once
#ifndef cabecalho
#define cabecalho

#define MAX_CID 20
#define MAX_CAR	10
#define MAX_NOME 200

char nome[MAX_NOME];
int num_cidades;
int num_carros;
int mat_distancia[MAX_CID][MAX_CID];
int mat_retorno[MAX_CID][MAX_CID];

void leArquivoNaoEuclideano(const char* caminho);

#endif // cabecalho
