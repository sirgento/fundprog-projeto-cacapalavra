#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "./resource/headers/funcoes.h"
#include "./resource/headers/typedefs.h"
#include "./resource/function/stackoverflow.h"

int main(int argc, char **argv) {
	setlocale(LC_ALL, " ");
	String inputFile, outputFile;
	FILE *iFile;
	FILE *oFile;
	bool stopar = false;
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
				printf("Dificuldade a jogar: (F)ácil, (M)édio, (D)ifícil: ");
				scanf(" %c", &dif);
				} while (!charIn(dif, "FfMmDd", 6));
				
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
					case 'M':
					case 'm':
						strcat(inputFile, "m/m");
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
	printf("%s\n%s\n%s\n", argv[0], inputFile, outputFile);
	
	iFile = fopen(inputFile, "r");
	oFile = fopen(outputFile, "w+");
	
	if (iFile == NULL) {
		printf("NULL_POINTER: Arquivo de entrada nulo!\n");
		stopar = true;
	}
	if (oFile == NULL) {
		printf("NULL_POINTER: Arquivo de saída nulo!\n");
		stopar = true;
	}
	/**
	 * Para a execução do código mediante exception.
	 * * */
	if (stopar) return -1;
	return 0;
}
