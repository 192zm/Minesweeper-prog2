#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"
#include <windows.system.h>
#define FLUSH fflush(stdin)
int all_mines = 0;
int mines = 0;
int diff = 0;
static int numOfPlayers = 0;
FILE* datoteka;
int t = 0;
int match = 0;
clock_t start;
clock_t end;
//PLAYER* playerArray;

void difficulty(PLAYER* player)
{
	diff = 0;
	do {
		printf("\t\t Odaberite tezinu(1 - lagano, 2- tesko, 3 - napredno) -  ");
		scanf("%d", &diff);
	} while ((diff != 1) && (diff != 2) && (diff != 3));

	FLUSH;
	//if ((diff != 1) && (diff != 2) && (diff != 3)) {
	//    printf("Unesite broj od 1-3");
	//    scanf("%f", &diff);
	//}

	if (diff == 1)
		level1(player);
	if (diff == 2)
		level2(player);
	if (diff == 3)
		level3(player);
}
void level1(PLAYER* player) {
	M = 5;
	N = 5;
	all_mines = 1;
	generator();
	guess(player);
}

void level2(PLAYER* player) {
	M = 10;
	N = 10;
	all_mines = 15;
	generator();
	guess(player);
}

void level3(PLAYER* player) {
	M = 16;
	N = 16;
	all_mines = 20;
	generator();
	guess(player);
}

void generator() {
	int i = 0, j = 0;
	srand((unsigned)time(NULL));
	while (j < N) {
		while (i < M) {
			minefield[i][j] = '-';
			empty_minefield[i][j] = minefield[i][j]; // spremi minefield u prazno polje ( pokazuje se igracu)
			final_minefield[i][j] = minefield[i][j]; // polje kad se klikne na bombu
			i++;
		}
		i = 0;
		j++;
	}
	mines = 0;
	while (mines < all_mines) // f-ja za generiranje mina, mines ce se povecavat i polje ce se punit minama sve dok je manje od total mines
	{
		i = rand() % (M); // uzmi random broj u intervalu od 0 do M
		j = rand() % (N);
		if (minefield[i][j] != '*')	// ako je mina na mjestu i,j , nemoj stavit minu na to mjesto
		{
			minefield[i][j] = '*';
			final_minefield[i][j] = minefield[i][j];
			mines++;
		}
	}
	i = 0;
	j = 0;
	while (j < N)      //  fja koja ispisuje koliko ima bombi u rasponu od odabranog podrucja                              
	{
		while (i < M)
		{
			if (minefield[i][j] != '*')
			{
				minefield[i][j] = 0;
			}
			if ((minefield[i - 1][j - 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i - 1][j] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i][j - 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i - 1][j + 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i + 1][j - 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i + 1][j] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i][j + 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			if ((minefield[i + 1][j + 1] == '*') && (minefield[i][j] != '*'))
			{
				minefield[i][j]++;
			}
			i++;
		}
		i = 0;
		j++;
	}
	i = 0;
	j = 0;
}
void print_minefield(void) {
	int i = 0, j = 0, z = 0;
	while (z < M)
	{
		if (z == 0)
		{
			printf("\t");
		}
		printf("|%d|\t", z);
		z++;
	}
	printf("\n\n");

	while (j < N)
	{
		printf("|%d|\t", j);
		while (i < M)
		{
			if (empty_minefield[i][j] == '-')
			{
				printf("|%c|\t", empty_minefield[i][j]);

			}
			else if (minefield[i][j] == 0)
			{
				empty_minefield[i][j] = 'B';
				printf("|%c|\t", empty_minefield[i][j]);
			}
			else
			{
				printf("|%d|\t", empty_minefield[i][j]);

			}
			i++;
		}
		match = 0;
		printf("\n");
		i = 0;
		j++;
	}
}

void guess(PLAYER* player) {
	int q = 0, i = 0, j = 0;
	print_minefield();
	while (j < N)
	{
		while (i < M)
		{
			if (minefield[i][j] == 0 && empty_minefield[i][j] == 'B')
				match++;
			if (empty_minefield[i][j] != 'B' && empty_minefield[i][j] != '-')
				match++;
			if (match == ((M * N) - all_mines))
				win(player);
			i++;
		}
		i = 0;
		j++;
	}
	printf("\n Unesite x vrijednost(stupac), razmak(space), pa y vrijednost(redak)");
	scanf("%d %d", &x, &y);

	FLUSH;
	if ((x >= M) || (x < 0) || (y < 0) || (y >= N)) // rekurzivna funkcija
	{
		printf("\n Molimo vas, ponovo unesite vrijednosti\n");
		guess(player);
	}
	if (minefield[x][y] == '*')
	{
		boom(player); //ako korisnik odabere minu, pokreni boom funkciju
		return;
	}
	if (empty_minefield[x][y] != '-')
	{
		printf("\n Unesite vrijednosti koje jos nisu bile unesene\n");
		guess(player);
	}
	else
	{
		empty_minefield[x][y] = minefield[x][y];
		if (minefield[x][y] == 0)
		{
			if (minefield[x - 1][y - 1] == 0)
			{
				empty_minefield[x - 1][y] = minefield[x - 1][y];
			}
			if (minefield[x - 1][y] == 0)
			{
				empty_minefield[x - 1][y] = minefield[x - 1][y];
			}
			if (minefield[x][y - 1] == 0)
			{
				empty_minefield[x][y - 1] = minefield[x][y - 1];
			}
			if (minefield[x - 1][y + 1] == 0)
			{
				empty_minefield[x - 1][y + 1] = minefield[x - 1][y + 1];
			}
			if (minefield[x + 1][y - 1] == 0)
			{
				empty_minefield[x + 1][y - 1] = minefield[x + 1][y - 1];
			}
			if (minefield[x + 1][y] == 0)
			{
				empty_minefield[x + 1][y] = minefield[x + 1][y];
			}
			if (minefield[x][y + 1] == 0)
			{
				empty_minefield[x][y + 1] = minefield[x][y + 1];
			}
			if (minefield[x + 1][y + 1] == 0)
			{
				empty_minefield[x + 1][y + 1] = minefield[x + 1][y + 1];
			}
		}
		guess(player);
	}
}

void boom(PLAYER* player) {
	final_field();
	printf("\n\t Pogodili ste minu na %d %d\n\tIzgubili ste!", x, y);
	play_again(player, t);
}
void final_field(void) {
	int i = 0, j = 0, z = 0;
	while (z < M) {
		if (z == 0)
			printf("\t");
		printf("|%d|\t", z);
		z++;
	}
	printf("\n\n");
	while (j < M) {
		printf("|%d|\t", j);
		while (i < M)
		{
			printf("|%c|\t", final_minefield[i][j]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
}
void win(PLAYER* player) {
	printf("\n\n\t\tPobjedili ste!!!!\n\n");
	long int timer = endTimer();
	player->best_score = timer;
	datoteka = fopen("igraci.bin", "rb+");
	if (datoteka == NULL) {
		perror("Spremanje igraca");
		exit(EXIT_FAILURE);
	}
	rewind(datoteka);
	fread(&numOfPlayers, sizeof(int), 1, datoteka);
	fseek(datoteka, sizeof(PLAYER) * numOfPlayers, SEEK_CUR);
	numOfPlayers++;
	fwrite(player, sizeof(PLAYER), 1, datoteka);
	rewind(datoteka);
	fwrite(&numOfPlayers, sizeof(int), 1, datoteka);

	fclose(datoteka);

	play_again(player, t);
}

PLAYER* sortBestScores(PLAYER* player, int index, int broj_igraca) {
	PLAYER temp = { 0 };
	int i, j;
	if (index == 1) {
		for (i = 0; i < broj_igraca; i++) {
			for (j = (i + 1); j < broj_igraca; j++) {
				if ((player + i)->best_score > (player + j)->best_score) {
					temp = *(player + i);
					*(player + i) = *(player + j);
					*(player + j) = temp;
				}
			}
		}
	}
	if (index == 2) {
		for (i = 0; i < broj_igraca; i++) {
			for (j = (i + 1); j < broj_igraca; j++) {
				if ((player + i)->best_score < (player + j)->best_score) {
					temp = *(player + i);
					*(player + i) = *(player + j);
					*(player + j) = temp;
				}
			}
		}
	}
	return player;
}

void play_again(PLAYER* player, int t) {
	char option[2];
	printf("\n\t\tHocete li igrati ponovo(Y/N/H)?:");
	scanf("%c", &option[0]);
	if ((option[0] == 'Y') || (option[0] == 'y')) {
		match = 0;
		startTimer();
		difficulty(player);

	}
	else if ((option[0] == 'N') || (option[0] == 'n')) {
		game_over();
	}
	else if ((option[0] == 'H' || option[0] == 'h')) {
		int broj_igraca = 0;
		FILE* pFile = fopen("igraci.bin", "rb");
		if (pFile == NULL) {
			perror("Ucitavanje igraca iz igraci.bin");
			return;
		}
		fread(&broj_igraca, sizeof(int), 1, pFile);
		printf("Broj igraca : %d\n", broj_igraca);
		PLAYER* playerArray = (PLAYER*)malloc(broj_igraca * sizeof(PLAYER));
		if (playerArray == NULL)
			return;
		fread(playerArray, sizeof(PLAYER), broj_igraca, pFile);
		rewind(pFile);
		char izbor;
		int index = 1;
		do {
			system("cls");
			playerArray = sortBestScores(playerArray, index, broj_igraca);
			printf("############################################################\n");
			for (int i = 0; i < broj_igraca; i++) {
				printf("Igrac %d. %s : rez:%d\n", i + 1, (playerArray + i)->name, (playerArray + i)->best_score);
			}
			printf("############################################################\n");
			printf("sortiranje po rezultatu\n  [1] najbolj - najgori\n  [2] najgori - najbolje\n");
			printf("  [x] izlaz iz prikaza\n");
			printf("############################################################\n");
			izbor = _getch();
			if (izbor == '1') {
				index = 1;
			}
			if (izbor == '2') {
				index = 2;
			}
		} while (izbor != 'x');
		play_again(player, t);
	}
	else
	{
		printf("Unesite Y za da ili N za ne ili H za sve igrace");
		play_again(player, t);
	}
}
void game_over(void) {
	printf("\n\n\tIgra je gotova");
	exit(1);
}

PLAYER* createPlayer() {
	PLAYER* tempAllocate = NULL;
	tempAllocate = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (tempAllocate == NULL) {
		return NULL;
	}
	return tempAllocate;
}



void createFile() {
	int broj = 0;
	if (datoteka = fopen("igraci.bin", "rb")) {
		fclose(datoteka);
	}
	else {
		datoteka = fopen("igraci.bin", "wb");
		if (datoteka == NULL) {
			perror("Kreiranje datoteke");
			exit(EXIT_FAILURE);
		}
		else {
			fwrite(&broj, sizeof(int), 1, datoteka);
			fclose(datoteka);
		}
	}
}
PLAYER* username(PLAYER* newPlayer) {
	datoteka = fopen("igraci.bin", "rb+");
	if (datoteka == NULL) {
		perror("Spremanje igraca");
		exit(EXIT_FAILURE);
	}
	rewind(datoteka);
	fread(&numOfPlayers, sizeof(int), 1, datoteka);
	newPlayer->id = numOfPlayers;
	printf("Unesite ime: ");
	scanf("%s", newPlayer->name);
	fclose(datoteka);
	return newPlayer;
}


clock_t startTimer() {
	start = clock();
	return start;
}

clock_t endTimer() {
	end = clock();
	return((end - start) / CLOCKS_PER_SEC);
}

