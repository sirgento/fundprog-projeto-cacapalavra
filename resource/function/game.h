#include <stdio.h>
/**
 * @return se uma string TGT contém uma string PARAM
 * * */
bool compararStrings(char *tgt, char *param, int length) {
	String paramCorrigido = "";
	int k = 0;
	for (int i = 0; i < length; i++) {
		/**
		 * Importante, compara com ponto, espaço e * pra ver se o usuário deixou em branco por engano
		 * * */
		if (!charIn(param[i], ". *", 3)) {
			paramCorrigido[k] = param[i];
			k++;
		}
	}
	paramCorrigido[k] = 0;
//	printf("CORRIGIDO: %s\n", paramCorrigido);
	
	/**
	 * String vazia não contém nada
	 * * */
	if (k == 0) return false;
	
	return (strstr(tgt, paramCorrigido) != NULL);
}

/**
 * Vide acima
 * * */
void limparString(char *str, int size) {
	String retorno = "";
	int k = 0;
	for (int i = 0; i < size; i++) {
		if (!charIn(str[i], ". *", 3)) {
			retorno[k] = str[i];
			k++;
		}
	}
	retorno[k] = 0;
	strcpy(str, retorno);
}

void removerStringEncontrada(char *param, char **tgt, int altura, int largura) {
	int indexCorreto = 0;
	for (int i = 0; i < altura; i++) {
		if (compararStrings(tgt[i], param, largura)) {
			indexCorreto = i;
			break;
		}
	}
	strcpy(tgt[indexCorreto], " ");
}

void jogar(FILE *out, char **desafio, char **palavras, int altura, int largura, int qtdPalavras) {
	printf("\nJogando!\n\n");
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
		for (int x = 0; x < altura; x++)
			fprintf(out, "Entrada do jogador: linha %d: %s\n", (x + 1), matrizEntrada[x]);
//			printf("%s\n", matrizEntrada[x]);

		bool achouHorizontal = false;
		char stringParaCompararH[] = "";
		/**
		 * Percorre a matriz horizontalmente
		 * * */
		for (int i = 0; i < altura; i++) {
			strcpy(stringParaCompararH, matrizEntrada[i]);
			stringParaCompararH[largura] = 0;
//			printf("%s\n", stringParaCompararH);
			int contagemLetras = 0;
			for (int n = 0; n < largura; n++) {
				if (!charIn(stringParaCompararH[n], ". *", 3))
				contagemLetras++;
			}
			if (contagemLetras == 1) break;
			if (compararStrings(desafio[i], stringParaCompararH, largura)) {
				limparString(stringParaCompararH, largura);
				printf("Parabéns! Você achou a palavra %s!\n", stringParaCompararH);
				fprintf(out, "Palavra encontrada: %s\n", stringParaCompararH);
				removerStringEncontrada(stringParaCompararH, palavras, altura, largura);
				achouHorizontal = true; 
				qtdPalavras--;
				break;
			}
//			printf("\n");
		}
		/**
		 * Comparação vertical é feita mediante condição, pois é mais intenso o requisito de processamento
		 * 100% sincero, não joguei isso pra uma função separada por um misto de "em cima da hora" e "preguiça"
		 * * */
		if (!achouHorizontal) {
			char stringParaCompararV[] = "";
			char stringComparacao[altura];
			char desafioComparacao[altura];
			char matrizInversa[largura][altura];
			char desafioInversa[largura][altura];
			/**
			 * Inverte as matrizes
			 * * */
			for (int j = 0; j < largura; j++) {
				for (int i = 0; i < altura; i++) {
					matrizInversa[j][i] = matrizEntrada[i][j];
					desafioInversa[j][i] = desafio[i][j];
				}
			}
			for (int i = 0; i < largura; i++) {
				for (int j = 0; j < altura; j++) {
					stringComparacao[j] = matrizInversa[i][j];
					desafioComparacao[j] = desafioInversa[i][j];
				}
				stringComparacao[altura] = 0;
				desafioComparacao[altura] = 0;
//				printf("%s\n", stringComparacao);
//				printf("%s\n", desafioComparacao);
				if (compararStrings(desafioComparacao, stringComparacao, altura)) {
					limparString(stringComparacao, altura);
					printf("Parabéns! Você achou a palavra %s!\n", stringComparacao);
					fprintf(out, "Palavra encontrada: %s\n", stringComparacao);
					removerStringEncontrada(stringComparacao, palavras, altura, largura);
					qtdPalavras--;
					break;
				}
			}
//				printf("\n");
		}
//		break;
		printf("Palavras restantes: %d\n", qtdPalavras);
		fprintf(out, "Palavras restantes: %d\n", qtdPalavras);
	} while (qtdPalavras > 0);
	printf("\nParabéns! Você venceu!\n");
}
