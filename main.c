#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "./resource/headers/funcoes.h"
#include "./resource/headers/typedefs.h"

int main(int argc, char **argv) {

	String inputFile, outputFile;
	/**
	 * Interrompe a execução do programa caso tenham sido passados
	 * parâmetros demais. Exibe uma mensagem solicitando que 
	 * verifique-se os dados inseridos.
	 * * * */
	if (argc > 3) {
		printf("ILLEGAL_ARGS: Too many arguments.\n");
		printf("Verifique a entrada de dados!\n");
		return -1;
	}
	/**
	 * Caso não tenham sido passados parâmetros suficientes,
	 * no caso, arquivo de entrada e saída, pergunta a dificuldade
	 * que o usuário quer jogar. Além disso, define o output padrão.
	 * * */
	else if (argc < 3) {
		char dif = ' ';
		printf("Caça-palavras v.0.1.\n");
		do {
		printf("Dificuldade a jogar: (F)ácil, (M)édio, (D)ifícil: ");
		scanf(" %c", &dif);
		} while (!charIn(dif, "FfMmDd", 6));
	} 
	
	setlocale(LC_ALL, " ");

	


}
