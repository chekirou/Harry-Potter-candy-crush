
#ifndef mecha

#define mecha
#include "constantes.h"
/*remplit une case  */
void loadGrille(int mat[10][11]);
void timetoChar(int time, char timechar[]);
int val_alea(int maxi);
void echanger(int *a, int *b);
int absa(int a);
void initialiser(int mat[10][11]);
int adjacente(int a, int b, int c, int d);
int verifier_unite(int a,int b, int mat[10][11]);
void suprimmer(int x, int y, int mar[10][11]);
void recurevite(int mat[10][11], int* score);

void recurvite_ligne(int ligne, int mat[10][11], int *score);
void recurevite_colonne(int colonne, int mat[10][11], int* score);
void evanesco(int type, int mat[10][11]);
void bombarda(int I,int J, int mat[10][11]);
int  aide(int mat[10][11], int *a, int *b, int *c, int *d);
#endif // mecha
