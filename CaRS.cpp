#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "CaRS.h"


int main(void) {

	leArquivoNaoEuclideano("Pequenas/Teste.txt");
	imprimeArquivoNaoEuclideano(" ");



	return 0;
}

void leArquivoNaoEuclideano(const char* caminho) {
	
	FILE* f = fopen(caminho, "r");
	
	char aux[200];

	if (f == NULL) {
		printf("Erro ao abrir o arquivo: %s\n", caminho);
		return;
	}
	// Leitura do nome
	fscanf(f, "%s %s %s", aux, aux, &nomeInstancia);
	
	// joga fora tipo e comentario
	fscanf(f, " %[^\n] ", aux);
	fscanf(f, " %[^\n] ", aux);
	

	// Leitura do numero de cidades
	fscanf(f, " %s %s %d", aux, aux ,&num_cidades);

	// Leitura do numero de carros
	fscanf(f, "%s %s %d", aux,aux, &num_carros);

	// joga fora tipo, formato e seção das arestas
	fscanf(f, " %[^\n]", aux);
	fscanf(f, " %[^\n]", aux);
	fscanf(f, " %[^\n]", aux);
	

	for (int i = 0; i < num_carros; i++) {
		fscanf(f, "%d", &mat_distancia[i][0][0]);
		for (int j = 0; j < num_cidades; j++) {
			for (int k = 0; k < num_cidades; k++) {
				fscanf(f, "%d", &mat_distancia[i][j][k]);
			}
		}
	}
	
	//joga fora seção de retorno
	fscanf(f, " %s", aux);

	for (int i = 0; i < num_carros; i++) {
		fscanf(f, "%d", &mat_retorno[i][0][0]);
		for (int j = 0; j < num_cidades; j++) {
			for (int k = 0; k < num_cidades; k++) {
				fscanf(f, "%d", &mat_retorno[i][j][k]);
			}
		}
	}
	
	
	fclose(f);
}

void imprimeArquivoNaoEuclideano(const char* arq) {
	FILE* f;
	if (!strcmp(arq, " ")) f = stdout;
	else f = fopen(arq, "w");
	
	fprintf(f,"Nome da Instancia: %s\n", nomeInstancia);
	fprintf(f,"Numero de Cidades: %d\n", num_cidades);
	fprintf(f,"Numero de Carros: %d\n", num_carros);
	fprintf(f,"Matriz de Distancias:\n");

	for (int i = 0; i < num_carros; i++) {
		fprintf(f,"Carro %d:\n", i);
		for (int j = 0; j < num_cidades; j++) {
			for (int k = 0; k < num_cidades; k++) {
				fprintf(f,"%3d ", mat_distancia[i][j][k]);
			}
			fprintf(f,"\n");
		}
		fprintf(f,"\n");
	}

	fprintf(f,"Matriz de Retornos:\n");
	for (int i = 0; i < num_carros; i++) {
		fprintf(f,"Carro %d:\n", i);
		for (int j = 0; j < num_cidades; j++) {
			for (int k = 0; k < num_cidades; k++) {
				fprintf(f,"%3d ", mat_retorno[i][j][k]);
			}
			fprintf(f,"\n");
		}
		fprintf(f,"\n");
	}
	
	if (strcmp(arq, " "))
		fclose(f);

}