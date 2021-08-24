#include <stdio.h>

void jogar(FILE *out, char **desafio, char **palavras, int altura, int largura, int qtdPalavras) {
	printf("Jogando\n");
	const int tamanhoCorrigido = (2 * largura) + 1;
	/**
	 * A matriz de entrada já vai ter sido corrigida
	 * * */
	char matrizEntrada[altura][largura + 1];
	do {
		setbuf(stdin, NULL);
		for (int i = 0; i < altura; i++) {
			int contagem = 0;
		/**
		 * String para entrada do jogador, para ter certeza que vai capturar tudo
		 * Declarada aqui dentro por que apresentou menos bugs
		 * * */
		char entradaJogador[tamanhoCorrigido];
			readString(tamanhoCorrigido, entradaJogador);
//			printf("%s\n", entradaJogador);
			for (int j = 0; j < largura; j++) {
				int k = j + contagem;
				while (entradaJogador[k] != '\n' && entradaJogador[k] != '\0') {
	//			printf("%c", st[k]);
					if (entradaJogador[k] == ' ') {
						k++;
						continue;
					} else {
						matrizEntrada[i][j] = entradaJogador[k];
						break;
					}
				}
				contagem++;
			}
			/**
			 * Setando caractere nulo para corrigir a matriz
			 * * */
			matrizEntrada[i][largura] = 0;
		}
//		for (int x = 0; x < altura; x++)
//			printf("%s\n", matrizEntrada[x]);

		/**
		 * Percorre a matriz horizontalmente
		 * * */
		for (int i = 0; i < altura; i++) {
			for (int j = 0; j < largura; j++) {
				printf("%c", matrizEntrada[i][j]);
			}
			printf("\n");
		}

		/**
		 * Percorre a matriz verticalmente
		 * * */
		for (int i = 0; i < largura; i++) {
			for (int j = 0; j < altura; j++) {
				printf("%c", matrizEntrada[j][i]);
			}
			printf("\n");
		}
		break;
//		printf("Palavras: %d\n", qtdPalavras);
		qtdPalavras--;
	} while (qtdPalavras > 0);
	
}
