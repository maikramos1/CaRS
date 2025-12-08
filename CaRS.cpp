#include <stdio.h>
#include "CaRS.h"

int main(void) {


	leArquivoNaoEuclideano();

	return 0;
}

void leArquivoNaoEuclideano(const char* caminho) {
	FILE* arquivo = fopen(caminho, "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo: %s\n", caminho);
		return;
	}
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
		printf("%s", buffer);
	}
	fclose(arquivo);
}