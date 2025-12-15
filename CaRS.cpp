#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "CaRS.h"


int main(void) {
	
	const char* entrada[] = {
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
	const char* saida[] = {
		//Instâncias Não-Euclideanas:
		//Pequenas
		"Pequenas/Mauritania10n.lp",
		"Pequenas/Bolivia10n.lp",
		//Médias
		"Medias/AfricaSul11n.lp",
		"Medias/Peru13n.lp",
		//Grandes
		"Grandes/Brasil16n.lp",
		"Grandes/Russia17n.lp"
	};
	int instancia = 0;

	
	leArquivoNaoEuclideano(entrada[instancia]);
	
	//escreveCEPLEX(saida[instancia]);
	escreveCEPLEX(" ");

	//const char* modelo = "Pequenas/Mauritania10n.lp";
	//const char* instancia2 = "teste";
	//const char* arq_solucao = "teste.txt";
	//const char* arq_res_obtidos = "resultados_obtidos.csv";

	//optimize_cplex(modelo, instancia2, arq_solucao, arq_res_obtidos);

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
	
	//8ª Restrição sendo dividida em 8.1 e 8.2
	//8.1ª Restrição
	for (int i = 1; i < num_cidades; i++) fprintf(f, "u_%d >= 2\n", i);

	//8.2ª Restrição
	for (int i = 1; i < num_cidades; i++) fprintf(f, "u_%d <= %d\n", i, num_cidades-1);

	//9ª Restrição
	//restrição maldita da desgaça
	for (int i = 1; i < num_cidades; i++) {
		for (int j = 1; j < num_cidades; j++) {
			fprintf(f, "u_%d - u_%d + 1 - %d", i, j, num_cidades - 2);
			for(int c = 0; c < num_carros; c++) {
				fprintf(f, " + %d f_%d_%d_%d", num_cidades - 2, c, i, j);
			}
			fprintf(f, " <= 0\n");
		}
	}

	//Antes da 10ª Restrição, declaro o bounds
	fprintf(f, "Bounds\n");
	for (int i = 1; i < num_cidades; i++) {
		fprintf(f, "u_%d >= 1\n", i);
	}
	
	//10ª Restrição
	fprintf(f,"BIN\n");
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				if (j == 0) {
					fprintf(f, "f_%d_%d_%d", c, i, j);
				}
				else {
					fprintf(f, " f_%d_%d_%d", c, i, j);
				}
			}
		}
	}
	fprintf(f, "\n");
	//suposição que no artigo está incorreto
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			for (int j = 0; j < num_cidades; j++) {
				if (j == 0) {
					fprintf(f, "w_%d_%d_%d", c, i, j);
				}
				else {
					fprintf(f, " w_%d_%d_%d", c, i, j);
				}
			}
		}
	}
	fprintf(f, "\n");
	//suposição que no artigo está incorreto também
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			if (i == 0) {
				fprintf(f, "a_%d_%d", c, i);
			}
			else {
				fprintf(f, " a_%d_%d", c, i);
			}
		}
	}
	fprintf(f, "\n");
	for (int c = 0; c < num_carros; c++) {
		for (int i = 0; i < num_cidades; i++) {
			if (i == 0) {
				fprintf(f, "e_%d_%d", c, i);
			}
			else {
				fprintf(f, " e_%d_%d", c, i);
			}
		}
	}
	fprintf(f, "\n");

	//11ª Restrição
	//Generals
	fprintf(f, "Gen\n");
	for (int i = 1; i < num_cidades; i++) {
		if (i == 1) {
			fprintf(f, "u_%d", i);
		}
		else {
			fprintf(f, " u_%d", i);
		}
	}
	fprintf(f, "\n");

	fprintf(f, "END");

	if (strcmp(arq, " "))
		fclose(f);
}

void optimize_cplex(const char* modelo, const char* instancia, const char* arq_solucao, const char* arq_res_obtidos) {
	int sts = 0;
	double sol = 0.0;
	double lb, gap, tempo_ini, tempo_fim, tempo;

	CPXENVptr env = NULL;
	CPXLPptr lp = NULL;

	env = CPXopenCPLEX(&sts);
	if (env == NULL) {
		fprintf(stderr, "Nao foi possivel abrir o ambiente CPLEX. (status code %d)\n", sts);
		exit(1);
	}

	sts = CPXsetintparam(env, CPX_PARAM_SCRIND, CPX_ON);
	check_status_cplex(env, sts, "CPXsetintparam(SCRIND)");

	sts = CPXsetdblparam(env, CPX_PARAM_TILIM, 3600.0);
	check_status_cplex(env, sts, "CPXsetdblparam(TILIM)");

	lp = CPXcreateprob(env, &sts, "meu_problema_lp");
	check_status_cplex(env, sts, "CPXcreateprob");

	sts = CPXreadcopyprob(env, lp, modelo, NULL);
	check_status_cplex(env, sts, "CPXreadcopyprob");

	sts = CPXgettime(env, &tempo_ini);
	check_status_cplex(env, sts, "CPXgettime(start)");

	sts = CPXmipopt(env, lp);
	check_status_cplex(env, sts, "CPXmipopt");

	sts = CPXgettime(env, &tempo_fim);
	check_status_cplex(env, sts, "CPXgettime(end)");

	tempo = tempo_fim - tempo_ini;

	sts = CPXgetobjval(env, lp, &sol);
	check_status_cplex(env, sts, "CPXgetobjval");

	sts = CPXgetbestobjval(env, lp, &lb);
	check_status_cplex(env, sts, "CPXgetbestobjval");

	sts = CPXgetmiprelgap(env, lp, &gap);
	check_status_cplex(env, sts, "CPXgetmiprelgap");

	int num_vars = CPXgetnumcols(env, lp);

	if (num_vars > 0) {
		double* var_values = new double[num_vars];
		char** var_names = new char* [num_vars];
		int names_buf_size;
		int surplus;
		char* names_buf = NULL;

		sts = CPXgetmipx(env, lp, var_values, 0, num_vars - 1);
		check_status_cplex(env, sts, "CPXgetmipx");

		sts = CPXgetcolname(env, lp, NULL, NULL, 0, &surplus, 0, num_vars - 1);
		if (sts != CPXERR_NEGATIVE_SURPLUS && sts != 0) {
			check_status_cplex(env, sts, "CPXgetcolname (chamada 1)");
		}

		names_buf_size = -surplus;

		if (names_buf_size > 0) {
			names_buf = new char[names_buf_size];

			sts = CPXgetcolname(env, lp, var_names, names_buf, names_buf_size, &surplus, 0, num_vars - 1);
			check_status_cplex(env, sts, "CPXgetcolname (chamada 2)");

			//escrever_relatorio_solucao(arq_solucao, sol, num_vars, var_values, var_names);

			FILE* f = fopen(arq_res_obtidos, "a");

			fprintf(f, "%s;%.0f;%.0f;%.4f;%.4f;", instancia, lb, sol, gap, tempo);

			fclose(f);
		}

		delete[] var_values;
		if (names_buf != NULL) {
			delete[] names_buf;
		}
		delete[] var_names;
	}
}

void check_status_cplex(CPXENVptr env, int sts, const char* function_name) {
	if (sts) {
		char error_string[CPXMESSAGEBUFSIZE];

		CPXgeterrorstring(env, sts, error_string);
		fprintf(stderr, "ERRO DO CPLEX na funcao %s: %s (status code %d)\n", function_name, error_string, sts);

		if (env) {
			CPXcloseCPLEX(&env);
		}

		exit(1);
	}
}