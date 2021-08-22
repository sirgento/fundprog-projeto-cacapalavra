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

void obterTamanhosLinhas(FILE *arq, int* linhas, int* colunas) {
	LongString st;
	int tamanhoAtual = 0;
	String tamanhos[2] = {"", ""};
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
	
	*linhas = atoi(tamanhos[0]);
	*colunas = atoi(tamanhos[1]);

}
/**
 * Bastante código reutilizado.
 * @return a quantidade de palavras a ser buscada
 * * */
int obterQuantidadesPalavras(FILE *arq) {
	LongString st;
	String tamanho = "";
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
			continue;
		else 
			strncat(tamanho, &st[i], 1);
	}
	
	return atoi(tamanho);
}

void criarMatrizArquivo(FILE *arq, char **matriz, int altura, int largura) {
	LongString st;
	
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
					matriz[i][j] = st[k];
					break;
				}
			}
			contagem++;
		}
	}
}
/**
 * Bastante código reutilizado. Favor referenciar a função criarMatrizArquivo(FILE, **char)
 * * */
void criarMatrizPalavras(FILE *arq, char **matriz, int quantidade) {
	String st;
	
	/**
	 * Percorre o arquivo e monta o array em memória
	 * * */
	for (int i = 0; i < quantidade; i++) {
		fgets(st, 64, arq);
		if (feof(arq)) 
			break;
		for (int j = 0; j < 64; j++) {
			int k = j;
			while (st[k] != '\n' && st[k] != '\0') {
				if (st[k] == ' ') {
					k++;
					continue;
				} else {
					matriz[i][j] = st[k];
					break;
				}
			}
			matriz[i][k + 1] = 0;
		}
	}
}















