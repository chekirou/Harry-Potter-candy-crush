#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>
#include <time.h>
#include "mechanique.h"
#include "constantes.h"
#include <SDL_mixer.h>
void loadGrille(int mat[10][11]){
    int i,j;
    for(i=0; i < 10; i++)
    {
        for(j= 0; j< 11; j++)
        {
            mat[i][j] = val_alea(5);
        }
    }
}
void timetoChar(int time, int *a, int *b)
{
    int i = 0, TimeTrans;
    time /= 1000;
    TimeTrans = time / 60;
    *a = TimeTrans;
    i++;
    TimeTrans = time % 60;
    *b = TimeTrans;
}
int val_alea(int maxi)
{


    return rand() % maxi;
}
void echanger(int *a, int *b)
{

    int r = *b;
    *b = *a;
    *a = r;
}
int absa(int a)
{

    if(a < 0)
    {
        return 0-a;
    }
    else
    {
        return a;
    }
}
int adjacente(int a, int b, int c, int d)
{

    if( ((a== c )&& absa(b-d) == 1)||(( b==d )&& (absa(a-c)== 1)))
    {
        return 1;

    }

    else{
        return 0;
    }
}
int verifier_unite(int a,int b, int mat[10][11])
{
    int objectif = mat[a][b]%5;


    int found =0;

        //gauche
        if(b> 0 && (mat[a][b-1] == objectif || mat[a][b-1] == objectif +5 || mat[a][b-1] == 10))
        {
            if(b > 1 && (mat[a][b-2]== objectif || mat[a][b-2] == objectif +5 || mat[a][b-2] == 10))
            {
                found = 1;
            }
            else if( b < 10&& ( mat[a][b+1] == objectif|| mat[a][b+1] == objectif +5 || mat[a][b+1] == 10))
            {

                found = 1;
            }
            else{
                found = 0;
            }
        }
        else if( b < 10 && (mat[a][b+1]== objectif || mat[a][b+1]== objectif+5 || mat[a][b+1] == 10))
        {

            if(b < 9 && (mat[a][b+2] == objectif || mat[a][b+2] == objectif+5 || mat[a][b+2] == 10))
            {
                found = 1;
            }
            else{
                found = 0;
            }

        }
        else
            {
                found = 0;
            }
        if(found==1)
        {
            return found;

        }
        else{
            if(a> 0 && (mat[a-1][b] == objectif || mat[a-1][b] == objectif + 5 || mat[a-1][b] == 10))
            {
                if(a > 1 && (mat[a-2][b] == objectif || mat[a-2][b] == objectif + 5 || mat[a-2][b] == 10))
                {
                    found = 1;
                }
                else if( a < 9&& ( mat[a+1][b] == objectif || mat[a+1][b] == objectif +5 || mat[a+1][b] == 10))
                {

                    found = 1;
                }
                else{
                    found = 0;
                }
            }
            else if( a< 9&&(mat[a+1][b] == objectif || mat[a+1][b] ==objectif+5 || mat[a+1][b] == 10))
            {

                if(a < 8&& (mat[a+2][b] == objectif || mat[a+2][b] ==objectif+5 || mat[a+2][b] ==10 ))
                {
                    found = 1;
                }

                else{
                    found = 0;
                }

            }
            else
            {
                found = 0;
            }
            return found;
        }


}
void suprimmer(int x, int y, int mat[10][11])
{
    int i = x;
    while(i>0)
    {
        mat[i][y] = mat[i-1][y];
        i--;
    }
    mat[0][y] = val_alea(5);
}

void recurevite(int mat[10][11], int *score, Mix_Music *musique)
{

    int i;
    for(i = 0; i< 10; i++)
    {
        recurvite_ligne(i, mat, score, musique);
        recurevite_colonne(i, mat, score, musique);
    }
    recurevite_colonne(10, mat, score, musique);

}


void recurvite_ligne(int ligne, int mat[10][11], int *score, Mix_Music *musique)
{
    int j,p, type, action2 =0, action3 = 0,Y;
        for(j =0; j< 11; j++)
        {
            type = mat[ligne][j] %5;
            p = j;
            do{

                if(mat[ligne][j] == type +5)
                {
                    action2 = 1;
                    Y = j;
                }
                else if(mat[ligne][j] == 10)
                {
                    action3 =1;
                    Y = j;
                }
                j++;
            }while(j < 11 && (mat[ligne][j] == type || mat[ligne][j] == type+5 || mat[ligne][j] == 10));
            if(j - p> 2)
            {

                
                if(action3 ==1){/*evanesco*/ *score += evanesco(type, mat); suprimmer(ligne, Y, mat);}
                else if(action2==1){ /*bombarda */*score += 9; bombarda(ligne, Y, mat);}
                else
                {
                    *score += 3;

                    suprimmer(ligne,p, mat);
                    switch(j-p)
                    {
                        case 3:
                        suprimmer(ligne,p+1, mat);
                        suprimmer(ligne,p+2, mat);

                        break;
                        case 4:
                            mat[ligne][p+1] = type+5;
                            suprimmer(ligne,p+2, mat);
                            suprimmer(ligne,p+3, mat);

                        break;
                        case 5:
                            suprimmer(ligne,p+1, mat);
                            mat[ligne][p+2] = 10;
                            suprimmer(ligne,p+3, mat);
                            suprimmer(ligne, p+4, mat);
                        break;
                    }

                }
                Mix_PlayMusic(musique, 1);
            }
            j--;
        }
}
void recurevite_colonne(int colonne, int mat[10][11], int* score, Mix_Music *musique)
{
    int i,p, type,action2 = 0, action3= 0,X;

        for(i =0; i< 10; i++)
        {
            type = mat[i][colonne] %5;
            p = i;
           do{

                if(mat[i][colonne] == type+5)
                {

                    action2 = 1;
                    X = i;
                }
                else if(mat[i][colonne] == 10)
                {
                    action3 =1;
                    X = i;
                }

                i++;
            }while(i < 10 && (mat[i][colonne] == type || mat[i][colonne] == type+5 || mat[i][colonne] == 10));
            if(i - p> 2)
            {
                
                if(action3==1){/*evanesco*/ suprimmer(X, colonne, mat); *score += evanesco(type, mat); }
                else if(action2==1){ /*bombarda */bombarda(X, colonne, mat); *score += 9;}
                else
                {*score += 3;

                    suprimmer(p, colonne, mat);
                    switch(i-p)
                    {
                        case 3:
                        suprimmer(p+1, colonne, mat);
                        suprimmer(p+2, colonne, mat);

                        break;
                        case 4:
                            mat[p+1][colonne] = type+5;
                            suprimmer(p+2, colonne, mat);
                            suprimmer(p+3, colonne, mat);

                        break;
                        case 5:
                            suprimmer(p+1, colonne, mat);
                            mat[p+2][colonne] = 10;
                            suprimmer(p+3, colonne, mat);
                            suprimmer(p+4, colonne, mat);
                        break;
                    }

                }
                Mix_PlayMusic(musique, 1);
            }
            i--;

        }

}
int evanesco(int type, int mat[10][11])
{
    int i = 9,j, d=0;
    while(i > -1)
    {
        j=10;
        while(j> -1)
        {
            if(mat[i][j] == type)
            {
                d++;
                suprimmer(i, j, mat);
                //mat[i][j] = val_alea(5);

            }
            j--;
        }
        i--;
    }
    return d;

}

void bombarda(int I,int J, int mat[10][11])
{
    if(J >0)
    {
        if(I >0)
        {
            suprimmer(I-1, J-1, mat);
            //suprimmer(I-1, J, mat);8
        }
        suprimmer(I, J-1, mat);
        if(I < 9){ suprimmer(I+1, J-1, mat);}
    }
    if(I >0)
    {
        suprimmer(I-1, J, mat);
    }
    suprimmer(I, J, mat);
    if(I < 9){ suprimmer(I+1, J, mat);}
    if(J< 10)
    {
         if(I >0)
        {
            suprimmer(I-1, J+1, mat);
        }
        suprimmer(I, J+1, mat);
        if(I < 9){ suprimmer(I+1, J+1, mat);}
    }



}
int aide(int mat[10][11], int *a, int *b, int *c, int *d)
{
    int i=0; int j, found =  0;
    while(i< 10 && !found)
    {
        j=0;
        while(j < 11 && !found)
        {
            *a= i;
            *b = j;

            if(j < 10 && !found)
            {
                echanger(&mat[i][j] , &mat[i][j+1]);
                if(verifier_unite(i, j+1, mat)==1)
                    {
                        found = 1;
                        *c = i;
                        *d = j+1;
                    }
                echanger(&mat[i][j] , &mat[i][j+1]);
            }
            if(i < 9 && !found)
            {
                echanger(&mat[i][j] , &mat[i+1][j]);
                if(verifier_unite(i+1, j, mat)==1)
                    {
                        found = 1;
                        *c = i+1;
                        *d = j;
                    }
                echanger(&mat[i][j] , &mat[i+1][j]);
            }
             if(j > 0 && !found)
            {
                echanger(&mat[i][j] , &mat[i][j-1]);
                if(verifier_unite(i, j-1, mat)==1)
                    {
                        found = 1;
                        *c = i;
                        *d = j-1;
                    }
                echanger(&mat[i][j] , &mat[i][j-1]);
            }
             if(i > 0 && !found)
            {
                echanger(&mat[i][j] , &mat[i-1][j]);
                if(verifier_unite(i-1, j, mat)==1)
                    {
                        found = 1;
                        *c = i-1;
                        *d = j;
                    }
                echanger(&mat[i][j] , &mat[i-1][j]);
            }
            j++;
        }
        i++;
    }
    return found;

}
