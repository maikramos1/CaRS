#include <stdio.h>
#include "CaRS.h"

int main(void) {


	leArquivoNaoEuclideano("Mautitania10n.car");
	imprimeArquivoNaoEuclideano();

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
	fscanf(f, "%s[7]", aux, &nomeInstancia);
	
	// joga fora tipo e comentario 
	fscanf(f, "%s", aux);
	fscanf(f, "%s", aux);

	// Leitura do numero de cidades
	fscanf(f, "%s %d", aux, &num_cidades);

	// Leitura do numero de carros
	fscanf(f, "%s %d", aux, &num_carros);

	// joga fora tipo, formato e seção das arestas
	fscanf(f, "%s", aux);
	fscanf(f, "%s", aux);
	fscanf(f, "%s", aux);

	/*
	for (int j = 0; j < num_obj; j++)
		fscanf(f, "%d", &vet_val_obj[j]);

	for (int j = 0; j < num_obj; j++)
		fscanf(f, "%d", &vet_pes_obj[j]);

	for (int i = 0; i < num_moc; i++)
		fscanf(f, "%d", &vet_cap_moc[i]);
	*/

	fclose(f);
}

void imprimeArquivoNaoEuclideano() {
	printf("Nome da Instancia: %s\n", nomeInstancia);
}