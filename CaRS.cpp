#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "CaRS.h"


int main(void) {
	
	const char* instancia[] = {
		//Instâncias Não-Euclideanas:
		//Pequenas
		"Pequenas/Mauritania10n.car",
		"Pequenas/Bolivia10n.car",
		//Médias
		"Medias/AfricaSul11n.car",
		"Medias/Peru13n.car",
		//Grandes
		"Grandes/Brasil16n.car",
		"Grandes/Russia17n.car"
	};

	
	leArquivoNaoEuclideano(instancia[0]);
	
	escreveCEPLEX(" ");

	//imprimeArquivoNaoEuclideano(" ");

	




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

void escreveCEPLEX(const char* arq) {
	// A implementar
	FILE* f;
	if (!strcmp(arq, " ")) f = stdout;
	else f = fopen(arq, "w");

	//FO -> 1ª Equação
	fprintf(f, "Min \n");
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				//trocando a ordem de D e F pra ficar igual no slide
				if (c == 0 && i == 0 && j == 0) {
					fprintf(f, "%d f_%d_%d_%d ", mat_distancia[c][i][j], c, i, j);
				}
				else {
					fprintf(f, "+ %d f_%d_%d_%d ", mat_distancia[c][i][j], c, i, j);
				}
				
			}
		}
	}
	fprintf(f, "+ ");
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				//entende-se y = gamma = taxa de retorno
				if (c == 0 && i == 0 && j == 0) {
					fprintf(f, "%d y_%d_%d_%d ", mat_retorno[c][i][j], c, i, j);
				}
				else {
					fprintf(f, "+ %d y_%d_%d_%d ", mat_retorno[c][i][j], c, i, j);
				}

			}
		}
	}
	//Subject To
	fprintf(f, "\nST\n");

	//2ª Restrição
	for (int i = 0; i < num_cidades; i++) {
		for (int c = 0; c < num_carros; c++) {
			for (int j = 0; j < num_cidades; j++) {
				if (c == 0 && j == 0) {
					fprintf(f, "f_%d_%d_%d ",c,i,j);
				}
				else {
					fprintf(f, "+ f_%d_%d_%d ", c, i, j);
				}
			}
		}
		fprintf(f,"= 1\n");
	}

	//3ª Restrição
	for (int j = 0; j < num_cidades; j++) {
		for (int c = 0; c < num_carros; c++) {
			for (int i = 0; i < num_cidades; i++) {
				if (c == 0 && i == 0) {
					fprintf(f, "f_%d_%d_%d ", c, i, j);
				}
				else {
					fprintf(f, "+ f_%d_%d_%d ", c, i, j);
				}
			}
		}
		fprintf(f, "= 1\n");
	}

	//4ª Restrição
	//linearizando e substituindo por 4.1, 4.2 e 4.3 (f c i j já é binária)
	//4.1ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "a_%d_%d", c,i);
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, " - f_%d_%d_%d", c, i, j);
			}
			fprintf(f, " <= 0\n");
		}
	}

	//4.2ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "a_%d_%d", c, i);
			for (int x = 0; x < num_carros; x++) {
				if (x != c) {
					for (int h = 0; h < num_cidades; h++) {
						fprintf(f, " - f_%d_%d_%d", x, h, i);
					}
				}
			}
			fprintf(f, " <= 0\n");
		}
	}

	//4.3ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "a_%d_%d", c, i);
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, " - f_%d_%d_%d", c, i, j);
			}
			for (int x = 0; x < num_carros; x++) {
				if (x != c) {
					for (int h = 0; h < num_cidades; h++) {
						fprintf(f, " - f_%d_%d_%d", x, h, i);
					}
				}
			}
			fprintf(f, " >= -1\n");
		}
	}

	//5ª Restrição
	//linearizando e substituindo por 5.1, 5.2 e 5.3 (f c i j já é binária)
	//5.1ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "e_%d_%d", c, i);
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, " - f_%d_%d_%d", c, j, i);
			}
			fprintf(f, " <= 0\n");
		}
	}

	//5.2ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "e_%d_%d", c, i);
			for (int x = 0; x < num_carros; x++) {
				if (x != c) {
					for (int h = 0; h < num_cidades; h++) {
						fprintf(f, " - f_%d_%d_%d", x, i, h);
					}
				}
			}
			fprintf(f, " <= 0\n");
		}
	}

	//5.3ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			fprintf(f, "e_%d_%d", c, i);
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, " - f_%d_%d_%d", c, j, i);
			}
			for (int x = 0; x < num_carros; x++) {
				if (x != c) {
					for (int h = 0; h < num_cidades; h++) {
						fprintf(f, " - f_%d_%d_%d", x, i, h);
					}
				}
			}
			fprintf(f, " >= -1\n");
		}
	}

	//6ª Restrição
	//linearizando e substituindo por 6.1, 6.2, 6.3 e adicionada no final w(c i j) como binária
	//6.1ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			//verificar a relação de j em w de acordo com o artigo
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, "w_%d_%d_%d - a_%d_%d <= 0\n", c, i, j, c, j);
			}
			
		}
	}

	//6.2ª Restrição
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, "w_%d_%d_%d - e_%d_%d <= 0\n", c, i, j, c, i);
			}
		}
	}

	//6.3ª Restrição
	for(int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				fprintf(f, "w_%d_%d_%d - a_%d_%d - e_%d_%d >= -1\n", c, i, j, c, j, c, i);
			}
		}
	}

	//7ª Restrição
	for(int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			if (c == i && c == 0)	fprintf(f, "a_%d_%d",c,i);
			else fprintf(f, " + a_%d_%d",c,i);
		}
	}
	fprintf(f, " >= 1\n");
	


	if (strcmp(arq, " "))
		fclose(f);
}