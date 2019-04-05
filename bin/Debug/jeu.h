#ifndef jeu

#define jeu
 typedef struct{

 	int time;
 	int score;
 	int mat[10][11];

 }backup;
void savegarder(int mat[10][11], int time, int score);
void chargermatrice(int mat[10][11], int *score, int *time);
void arret(SDL_Surface *ecran, int score, int option, int mat[10][11], int time);


void check(int* etape, int a,int b,int c, int d, int mat[10][11], int* score);
void jouer(SDL_Surface* ecran, int option);

void humainMachine();


#endif // jeu
