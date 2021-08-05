#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @function Reads a string into a given variable
 * @param tam = String length, svar = the string
 * @return void
 * */
void readString(int tam, char svar[]) {
	fgets(svar, tam, stdin);	
	svar[strcspn(svar, "\n")] = '\0';
	setbuf(stdin, NULL);
}

/**
 * @function Verifies if a character exists within a string.
 * @param param = the char to look for, tgt = the string, size = the string size
 * @return true if char is in string, else false
 * */
bool charIn(char param, char tgt[], int size) {
	for (int i = 0; i < size; i++) {
		if (param == tgt[i]) return true;
	}
	return false;
}
