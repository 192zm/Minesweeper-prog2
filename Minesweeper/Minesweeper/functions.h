#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
typedef struct player {
	char name[20];
	int best_score;
	int id;
}PLAYER;
void difficulty(PLAYER* player);
void level1(PLAYER* player);
void level2(PLAYER* player);
void level3(PLAYER* player);
void generator(void);
void guess(PLAYER* player);
void boom(PLAYER* player);
void final_field(void);
void win(PLAYER* player);
void play_again(PLAYER* player, int t);
void game_over(void);
PLAYER* createPlayer();
void createFile();
PLAYER* username(PLAYER* newPlayer);
clock_t startTimer();
clock_t endTimer();
PLAYER* sortBestScores(PLAYER* player, int index, int broj_igraca);

int x, y;
int M, N;
extern int diff;
extern int all_mines;
extern int mines;
int minefield[17][17];
int empty_minefield[17][17];
int final_minefield[17][17];
#endif	
