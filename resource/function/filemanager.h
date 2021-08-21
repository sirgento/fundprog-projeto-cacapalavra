#include <stdio.h>
#include <stdbool.h>
#include "../headers/typedefs.h"

void printarLinhasArquivo(FILE *arq) {
	LongString st;
	while (true) {
		fgets(st, 128, arq);
		if (feof(arq)) 
			break;
		if (!charIn('#', st, 2))
			printf("%s", st);
	}
}

void criarMatrizArquivo(FILE *arq, char **matriz) {
	LongString st;
	int tamanhoAtual = 0;
	String tamanhos[2] = {"", ""};
	int altura, largura;
	/**
	 * Lê a primeira linha válida do arquivo -- o tamanho da matriz
	 * * */
	while (true) {
		fgets(st, 128, arq);
		if (!charIn('#', st, 2))
//			printf("%s", st);
			break;
	}
	
	/**
	 * Converte a linha em ints separados pra altura e largura
	 * * */
	for (int i = 0; (st[i] != '\n' && st[i] != '\0'); i++) {
		if (st[i] == ' ')
			tamanhoAtual++;
		else 
			strncat(tamanhos[tamanhoAtual], &st[i], 1);
	}
	altura = atoi(tamanhos[0]);
	largura = atoi(tamanhos[1]);
	
//	printf("Altura = %d, largura = %d\n", altura, largura);
	
	/**
	 * Inicializa a matriz como nula.
	 * Reutiliza a variável tamanhoAtual.
	 * * */
	tamanhoAtual = altura * largura;
	matriz = (char **) malloc(altura * sizeof(char *));
	for (int i = 0; i < altura; i++) {
		matriz[i] = (char *) malloc(largura * sizeof(char));
	}
//	printf("%d, %d\n",tamanhoAtual, sizeof(matriz));
	
	/**
	 * Percorre o arquivo e monta o array em memória
	 * * */
	for (int i = 0; i < altura; i++) {
		int contagem = 0;
		fgets(st, 128, arq);
		if (feof(arq)) 
			break;
//		printf("%s", st);
		for (int j = 0; j < largura; j++) {
			int k = j + contagem;
			while (st[k] != '\n' && st[k] != '\0') {
//			printf("%c", st[k]);
				if (st[k] == ' ') {
					k++;
					continue;
				} else {
//					if (j == 0) 
						matriz[i][j] = st[k];
//					else
//						matriz[i][j] = st[k + count];
//					k++;
					break;
				}
//			if (i % 2 == 0)
//				matriz[i][j] = (char) (65 + i + j);
//			else
//				matriz[i][j] = (char) (97 + i + j);
			}
			contagem++;
		}
	}
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++) {
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}
}

