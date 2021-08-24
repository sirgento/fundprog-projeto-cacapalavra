#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "./resource/headers/funcoes.h"
#include "./resource/headers/typedefs.h"
#include "./resource/function/stackoverflow.h"
#include "./resource/function/filemanager.h"
#include "./resource/function/game.h"

void doGame(String, String);

int main(int argc, char **argv) {
	setlocale(LC_ALL, " ");
	String inputFile, outputFile;
	/**
	 * Interrompe a execução do programa caso tenham sido passados
	 * parâmetros demais. Exibe uma mensagem solicitando que 
	 * verifique-se os dados inseridos.
	 * * * */
	if (argc > 3) {
		printf("ILLEGAL_ARGS: Too many arguments.\n");
		printf("Verifique a entrada de dados!\n");
		return -1;	}
	/**
	 * Caso não tenham sido passados parâmetros suficientes,
	 * no caso, arquivo de entrada e saída, pergunta a dificuldade
	 * que o usuário quer jogar. Além disso, define o output padrão.
	 * * */
	else if (argc < 3) {
		strcpy(outputFile, "./default-output.txt");
		switch (argc) {
			/**
			 * Caso nada tenha sido informado
			 * * */
			case 1:
				char dif = ' ';
				printf("Caça-palavras v.0.1.\n");
				do {
				printf("Dificuldade a jogar: (F)ácil, (D)ifícil: ");
				scanf(" %c", &dif);
				} while (!charIn(dif, "FfDd", 4));
				
				strcpy(inputFile, "./resource/difc/");
				char p[2];
				int i = randomIntInterval(1,3);
				itoarr(i, p);
				switch(dif) {
					case 'F':
					case 'f': 
						strcat(inputFile, "e/e");
						strcat(inputFile, p);
						break;
					case 'D':
					case 'd': 
						strcat(inputFile, "h/h");
						strcat(inputFile, p);
						break;
				}
				strcat(inputFile, ".txt");
				break;
			/**
			 * Caso tenha sido informado apenas o arquivo de entrada
			 * * */
			case 2: 
				strcpy(inputFile, argv[1]);
				break;
	}	}
	/**
	 * Caso padrão
	 * * */
	else {
		strcpy(inputFile, argv[1]);
		strcpy(outputFile, argv[2]);
	}
	/**
	 * Printa o nome dos arquivos a título de debug.
	 * * */
//	printf("%s\n%s\n%s\n", argv[0], inputFile, outputFile);
	
	doGame(inputFile, outputFile);
	
	return 0;
}

void doGame(String input, String output) {

	FILE *iFile;
	FILE *oFile;

	bool stopar = false;
	int altura = 0;
	int largura = 0;
	int quantidadePalavras = 0;
	char **matriz;
	char **palavrasValidas;
	
	/**
	 * Tenta abrir os arquivos. Para o código mediante exception.
	 * * */
	iFile = fopen(input, "r");
	oFile = fopen(output, "w+");
	
	if (iFile == NULL) {
		printf("NULL_POINTER: Arquivo de entrada nulo!\n");
		return;
	}
	if (oFile == NULL) {
		printf("NULL_POINTER: Arquivo de saída nulo!\n");
		return;
	}
	
	obterTamanhosLinhas(iFile, &altura, &largura);
//	printf("%d %d\n", altura, largura);
	
	/**
	 * Inicializa a matriz.
	 * * */
	matriz = (char **) malloc(altura * sizeof(char *));
	for (int i = 0; i < altura; i++) {
		matriz[i] = (char *) malloc(largura * sizeof(char));
	}
	
	criarMatrizArquivo(iFile, matriz, altura, largura);
	/**
	 * Obtém a quantidade de Palavras.
	 * * */
	quantidadePalavras = obterQuantidadesPalavras(iFile);
	printf("\nAtenção! O sistema diferencia entre letras maiúsculas e minúsculas!\nPalavras a encontrar: %d\n", quantidadePalavras);
	
	printf("Seu desafio: \n\n");
	
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++) {
//			printf("%d %d ", i, j);
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}
	
	/**
	 * Inicializa a matriz Palavras.
	 * Utiliza String = char[64] para ter certeza
	 * * */
	palavrasValidas = (char **) malloc(quantidadePalavras * sizeof(char *));
	for (int i = 0; i < quantidadePalavras; i++) {
		palavrasValidas[i] = (char *) malloc(64 * sizeof(char));
	}

	criarMatrizPalavras(iFile, palavrasValidas, quantidadePalavras);
	
	printf("\nFormatos de entrada válidos(exemplos):\n");
	printf("\n* * * * *   * * *\n* P R G *   * P *\n* * * * *   * R *\n");
	printf("            * G *\n            * * *\n\n");
	
	for (int i = 0; i < quantidadePalavras; i++) {
		printf("%s\n", palavrasValidas[i]);
	}

	do {
		jogar(oFile, matriz, palavrasValidas, altura, largura, quantidadePalavras);
		return;
	} while(true);
}




