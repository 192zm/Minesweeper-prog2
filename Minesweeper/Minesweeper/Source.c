#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"
#define FLUSH fflush(stdin)
extern FILE* datoteka = NULL;
int main() {
	createFile();
	PLAYER* newPlayer = createPlayer();
	startTimer();
	difficulty(username(newPlayer));


	return 0;
}
