#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>

#include "mechanique.h"
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "jeu.h"













void check(int* etape, int a,int b,int c, int d, int mat[10][11], int* score)
{
            if(*etape ==2)
            {
                // on verifie si elles sont adjacentes
                if(adjacente(a,b,c,d)==1)
                {
                    echanger(&mat[b][a], &mat[d][c]);
                    *etape = 3;
                }
                //si elles ne le sont pas alors on revient a l'etape 1
                else
                {
                   *etape = 0;
                }
            }
            else if(*etape == 4)
            {
                //on verifie si ils ne sont pas dans un alignement dans un alignement
                if((verifier_unite(b,a, mat)==  0 ) && (verifier_unite(d,c, mat) ==  0))
                {
                    echanger(&mat[b][a], &mat[d][c]);
                    *score -=1;
                }
                *etape =0;
            }
}




















void jouer(SDL_Surface *ecran, int option)
{

    SDL_Surface *background = NULL, *shade = NULL, *shade2 = NULL, *time = NULL, *timeleft = NULL, *boutonhelp = NULL;
    SDL_Surface *scoreText = NULL, *Score = NULL, *cup= NULL, *de = NULL, *houses= NULL, *arretB = NULL, *bouton = NULL;
    SDL_Surface *gryffondor = NULL, *ravenclaw = NULL, *hufflepuff = NULL, *slytherin = NULL,* ministry = NULL, *sword = NULL, *locket = NULL, *tiarra = NULL;
    SDL_Rect pos;
    SDL_Event event;
    TTF_Font *police = NULL;
    int mat[10][11], i,j, continuer = 1, etape =0, startTime = 0, endTime = 0, RES =0, departingTime = 300000;
    int a,b, c, d;
    char TIME[4], Cscore[10];
    SDL_Color noir =  {0,0,0};
    TTF_Init();

    background = IMG_Load("playscreen.jpg");
    //cadre = IMG_Load("imagecadre.png");
    arretB = IMG_Load("boutonarret.png");
    shade = IMG_Load("light.png");
    shade2 = IMG_Load("darkness.png");
    gryffondor =IMG_Load("gryffondor.png");
    hufflepuff = IMG_Load("hufflepuff.png");
    ravenclaw = IMG_Load("ravenclaw.png");
    slytherin = IMG_Load("slytherin.png");
    ministry = IMG_Load("ministry.png");
    sword = IMG_Load("sword.png");
    cup = IMG_Load("cup.png");
    de = IMG_Load("death_mark.png");
    tiarra = IMG_Load("diademe.png");
    locket = IMG_Load("locket.png");
    houses = IMG_Load("howarts.png");
    police = TTF_OpenFont("calibri.ttf", 26);
    time= TTF_RenderText_Blended(police, "temps restant : ", noir);
    scoreText = TTF_RenderText_Blended(police, "le score", noir);
    boutonhelp = IMG_Load("boutonaide.png");
    bouton = IMG_Load("retourB.png");





    if(!option)
    {
        loadGrille(mat);RES = 0;
    }
    else
    {
        chargermatrice(mat, &RES, &departingTime );
    }







    recurevite(mat, &RES);


    while(continuer)
    {

        SDL_PollEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
             break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {continuer =0;}
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.x > Xcanvas && event.button.x < 955 && event.button.y > 5 && event.button.y <605)
            {
               switch(etape)
                {
                    case 0:
                        a =(event.button.x - Xcanvas) / 60;
                        b = (event.button.y - Ycanvas) / 60;
                        etape++;
                        break;
                    case 1:
                        c =(event.button.x- Xcanvas) / 60;
                        d = (event.button.y- Ycanvas) / 60;
                        etape++;
                        break;
                }
            }
            else if(event.button.x > Xhelp && event.button.x < EXhelp && event.button.y > Yhelp && event.button.y <EYhelp)
            {
                if(aide(mat, &b, &a, &d, &c))
                {
                    etape =5;
                }
                else
                {
                    loadGrille(mat);
                    etape = 0;
                }
            }
            else if(event.button.x > Xpause && event.button.x < 60 && event.button.y > Ypause && event.button.y < 250)
            {
                loadGrille(mat);

            }

            else if(event.button.x > Xarret && event.button.x < 60 && event.button.y > Yarret && event.button.y < Yarret+50)
            {
                
                arret(ecran, RES, 1, mat, departingTime - endTime);
                continuer = 0;
            }
        break;
        }
       if(departingTime - endTime <0)
        {
            continuer = 0;
            arret(ecran, RES, 0, mat, 0);
        }




        endTime = SDL_GetTicks();
        if(endTime- startTime >  500)
        {
            check(&etape, a,b,c,d,mat, &RES);
            if(etape == 3)
            {
                etape++;
            }
            else
            {
                recurevite(mat, &RES);
            }





            timetoChar(departingTime - endTime, TIME);
            //SDL_FreeSurface(timeleft);
            timeleft =TTF_RenderText_Blended(police,TIME, noir);
            sprintf(Cscore, "%d", RES);
            //SDL_FreeSurface(Score);
            Score = TTF_RenderText_Blended(police, Cscore, noir);





                /** les blits **/
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
            pos.x = 0;
            pos.y = 0;
            //SDL_BlitSurface(background, NULL, ecran, &pos);

                pos.x = timeX;
                pos.y = timeY;
                SDL_BlitSurface(time, NULL, ecran, &pos);
                pos.y += 50;
                SDL_BlitSurface(timeleft, NULL, ecran, &pos);
                pos.x = Xscore;
                pos.y = Yscore;
                SDL_BlitSurface(scoreText, NULL, ecran, &pos);
                pos.y += 50;
                SDL_BlitSurface(Score, NULL, ecran, &pos);
                pos.x = Xhelp;
                pos.y = Yhelp;
                SDL_BlitSurface(boutonhelp, NULL, ecran, &pos);
                pos.x = Xpause;
                pos.y = Ypause;
                SDL_BlitSurface(bouton, NULL, ecran, &pos);
                pos.x = Xarret;
                pos.y = Yarret;
                SDL_BlitSurface(arretB, NULL, ecran, &pos);
                if(etape > 0)
                    {
                        pos.x = Xcanvas + LARGEUR_CELLULE * a;
                        pos.y = Ycanvas + HAUTEUR_CELLULE * b;
                        SDL_BlitSurface(shade, NULL, ecran, &pos);
                    }
                if(etape > 1 )
                {
                    pos.x = Xcanvas + LARGEUR_CELLULE * c;
                    pos.y = Ycanvas + HAUTEUR_CELLULE * d;
                    SDL_BlitSurface(shade2, NULL, ecran, &pos);
                }

                for(i = 0; i< 10; i++)
                {
                    for(j= 0; j< 11; j++)
                    {
                        pos.x = Xcanvas + LARGEUR_CELLULE * j;
                        pos.y = Ycanvas + HAUTEUR_CELLULE * i;
                        switch(mat[i][j])
                        {
                        case 0:
                            SDL_BlitSurface(gryffondor, NULL, ecran, &pos);
                            break;
                        case 1:
                            SDL_BlitSurface(hufflepuff, NULL, ecran, &pos);
                            break;
                            case 2:
                            SDL_BlitSurface(ravenclaw, NULL, ecran, &pos);
                            break;
                        case 3:
                            SDL_BlitSurface(slytherin, NULL, ecran, &pos);
                            break;
                        case 4:
                            SDL_BlitSurface(ministry, NULL, ecran, &pos);
                            break;
                        case 5:
                            SDL_BlitSurface(sword, NULL, ecran, &pos);
                            break;
                        case 6:
                            SDL_BlitSurface(cup, NULL, ecran, &pos);
                            break;
                        case 7:
                            SDL_BlitSurface(tiarra, NULL, ecran, &pos);
                            break;
                        case 8:
                            SDL_BlitSurface(locket, NULL, ecran, &pos);
                            break;
                        case 9:
                            SDL_BlitSurface(de, NULL, ecran, &pos);
                            break;
                         case 10:
                            SDL_BlitSurface(houses, NULL, ecran, &pos);
                            break;
                        }
                    }
                }
                if(etape == 5)
                    etape = 0;
                SDL_Flip(ecran);
                startTime = endTime;
            }
            else
            {
                SDL_Delay(500- (endTime - startTime));
            }


        }
        SDL_FreeSurface(background);
        SDL_FreeSurface(shade2);
        SDL_FreeSurface(timeleft);
        SDL_FreeSurface(time);
        SDL_FreeSurface(shade);
        SDL_FreeSurface(gryffondor);
        SDL_FreeSurface(hufflepuff);
        SDL_FreeSurface(ravenclaw);
        SDL_FreeSurface(slytherin);
        SDL_FreeSurface(ministry);
        SDL_FreeSurface(sword);
        SDL_FreeSurface(tiarra);
        SDL_FreeSurface(cup);
        SDL_FreeSurface(locket);
        SDL_FreeSurface(de);
        SDL_FreeSurface(houses);
        SDL_FreeSurface(scoreText);
        SDL_FreeSurface(Score);
        SDL_FreeSurface(time);
        SDL_FreeSurface(timeleft);
        SDL_FreeSurface(boutonhelp);
        SDL_FreeSurface(bouton);
        SDL_FreeSurface(arretB);
}




















void sauvegarder(int mat[10][11], int time, int score)
{

    FILE* f = NULL;
    int i,j;
    f = fopen("matrice", "w");
    if(f != NULL)
    {
        backup *B = NULL;
        B = ( backup*) malloc(sizeof(backup));
        for(i=0; i < 10; i++)
        {
            for(j= 0; j< 11; j++)
            {
                B->mat[i][j] = mat[i][j];
            }
        }
        B->score = score;
        B->time = time;
        fwrite(B, sizeof(backup), 1, f);
        fclose(f);
        free(B);
    }



}





void chargermatrice(int mat[10][11], int *score, int *time)
{
    FILE* f = NULL;
    int i,j;
    f = fopen("matrice", "r");
    if(f != NULL)
    {
        backup B;
        fread(&B, sizeof(backup), 1 , f);
        for(i=0; i < 10; i++)
        {
            for(j= 0; j< 11; j++)
            {
                 mat[i][j]= B.mat[i][j];
            }
        }
        *score =  B.score;
        *time = B.time;
        fclose(f);
    }
}


















void arret(SDL_Surface *ecran, int score, int option, int mat[10][11], int time)
{
    SDL_Surface *back = NULL, *scoreText = NULL, *message = NULL, *felicitation = NULL, *meilleur = NULL, *boutonsave = NULL;
    SDL_Rect pos;
    SDL_Event event;
    TTF_Font *police = NULL;
    back = IMG_Load("endscreen.jpg");
    char resultat[30], est[40];
    int continuer =1, bestSCore, youdid  =0;
    SDL_Color noir =  {0,0,0};
    TTF_Init();
    police = TTF_OpenFont("calibri.ttf", 30);
    sprintf(resultat, "votre score final %d", score);
    message= TTF_RenderText_Blended(police, "temps ecoule", noir);
    felicitation= TTF_RenderText_Blended(police, "meilleur score !!!", noir);
    scoreText = TTF_RenderText_Blended(police, resultat, noir);

    if(!option)
    {
        FILE* f = NULL;
        f = fopen("scores", "r+");
        int SC;
        if(f != NULL)
        {

            fread(&SC, sizeof(int), 1 , f);

            bestSCore = SC;
            if(score >= SC)
            {
                youdid = 1;
                SC = score;
                rewind(f);
                fwrite(&SC, sizeof(int), 1, f);
                bestSCore = SC;
                }
        fclose(f);
        }

    }
    else if(option)
    {
        boutonsave = IMG_Load("boutonsave.png");
    }
     while(continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {continuer =0;}

                break;
            case SDL_MOUSEBUTTONDOWN:
                if(option &&(event.button.x > (LARGEUR_FENETRE / 2) - 100 && event.button.x < (LARGEUR_FENETRE / 2)+75 && event.button.y > (HAUTEUR_FENETRE /2)+20 && event.button.y < (HAUTEUR_FENETRE /2) +85))
                {
                    sauvegarder(mat, time, score);
                    continuer = 0;
                }
            break;

            }
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100,100,100));
            pos.x = 0;
            pos.y = 0;
            SDL_BlitSurface(back, NULL, ecran, &pos);
            pos.x = (LARGEUR_FENETRE / 2) - 100;
            pos.y = (HAUTEUR_FENETRE /2) - 150;
            SDL_BlitSurface(message, NULL, ecran, &pos);
            pos.y += 100;
            SDL_BlitSurface(scoreText, NULL, ecran, &pos);
            if(youdid && !option)
            {

                pos.y += 100;
                SDL_BlitSurface(felicitation, NULL, ecran, &pos);
            }
            if(!option)
            {
                sprintf(est, "meilleur score %d", bestSCore);
                SDL_FreeSurface(meilleur);
                meilleur = TTF_RenderText_Blended(police, est, noir);

                pos.y += 70;
                SDL_BlitSurface(meilleur, NULL, ecran, &pos);
            }
            else
            {
                pos.y += 70;
                SDL_BlitSurface(boutonsave, NULL, ecran, &pos);
            }
            SDL_Flip(ecran);
        }
        SDL_FreeSurface(felicitation);
        SDL_FreeSurface(meilleur);
        SDL_FreeSurface(message);
        SDL_FreeSurface(scoreText);
        SDL_FreeSurface(back);

}











































void humainMachine()
{

    SDL_Surface *ecran2 = NULL , *background = NULL, *shade = NULL, *shade2 = NULL, *time = NULL, *timeleft = NULL, *boutonhelp = NULL;
    SDL_Surface *scoreText = NULL, *Score = NULL,*score2 = NULL, *cup= NULL, *de = NULL, *houses= NULL, *arretB = NULL, *bouton = NULL;
    SDL_Surface *gryffondor = NULL, *ravenclaw = NULL, *hufflepuff = NULL, *slytherin = NULL,* ministry = NULL, *sword = NULL, *locket = NULL, *tiarra = NULL;
    SDL_Rect pos;
    SDL_Event event;
    TTF_Font *police = NULL;

    int mat1[10][11], mat2[10][11], i,j, continuer = 1,etape2=0, etape =0, startTime = 0, endTime = 0, RES1 =0, RES2 = 0, departingTime = 300000;
    int a,b, c, d, x,y,w,z;
    char TIME[4], Cscore[10];
    SDL_Color noir =  {0,0,0};
    ecran2 = SDL_SetVideoMode(LARGEUR_FENETRE2, HAUTEUR_FENETRE2, 32, SDL_HWSURFACE);

    TTF_Init();

    background = IMG_Load("playscreen.jpg");
    //cadre = IMG_Load("imagecadre.png");
    arretB = IMG_Load("boutonarret.png");
    shade = IMG_Load("light.png");
    shade2 = IMG_Load("darkness.png");
    gryffondor =IMG_Load("gryffondor.png");
    hufflepuff = IMG_Load("hufflepuff.png");
    ravenclaw = IMG_Load("ravenclaw.png");
    slytherin = IMG_Load("slytherin.png");
    ministry = IMG_Load("ministry.png");
    sword = IMG_Load("sword.png");
    cup = IMG_Load("cup.png");
    de = IMG_Load("death_mark.png");
    tiarra = IMG_Load("diademe.png");
    locket = IMG_Load("locket.png");
    houses = IMG_Load("howarts.png");
    police = TTF_OpenFont("calibri.ttf", 26);
    time= TTF_RenderText_Blended(police, "temps restant : ", noir);
    scoreText = TTF_RenderText_Blended(police, "le score", noir);
    boutonhelp = IMG_Load("boutonaide.png");
    bouton = IMG_Load("retourB.png");

    for(i = 0; i < 10; i++)
    {
        for(j=0; j< 11; j++)
        {
            mat1[i][j] = mat2[i][j] = val_alea(5);
        }
        RES1 = RES2 = 0;
    }








    recurevite(mat1, &RES1);
    recurevite(mat2, &RES2);

    while(continuer)
    {

        SDL_PollEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
             break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {continuer =0;}
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.x > Xcanvas2 && event.button.x < EXcanvas2  && event.button.y > Ycanvas2 && event.button.y < EYcanvas2)
            {
               switch(etape)
                {
                    case 0:
                        a =(event.button.x - Xcanvas2) / 60;
                        b = (event.button.y - Ycanvas2) / 60;
                        etape++;
                        break;
                    case 1:
                        c =(event.button.x- Xcanvas2) / 60;
                        d = (event.button.y- Ycanvas2) / 60;
                        etape++;
                        break;
                }
            }

            else if(event.button.x > Xpause2 && event.button.x < 60 && event.button.y > Ypause2 && event.button.y < 250)
            {
                loadGrille(mat1);

            }

            else if(event.button.x > Xarret2 && event.button.x < 160 && event.button.y > Yarret2 && event.button.y < Yarret2+50)
            {
                continuer = 0;
                arret(ecran2, RES1, 0, mat1, departingTime - endTime);
            }
        break;
        }
       if(departingTime - endTime <0)
        {
            continuer = 0;
            arret(ecran2, RES1, 0, mat1, 0);
        }




        endTime = SDL_GetTicks();
        if(endTime- startTime >  500)
        {
            recurevite(mat2, &RES2);
            if(etape2 ==0)
            {
                if(aide(mat2, &x, &w, &z, &y) == 1)
                {
                echanger(&mat2[x][w], &mat2[z][y]);
                etape2 = 2;
                }
                else
                {
                loadGrille(mat2);
                }

            }

            //check(&etape, a,b,c,d,mat2, &RES2);

            check(&etape, a,b,c,d,mat1, &RES1);
            if(etape == 3)
            {
                etape++;
            }
            else
            {
                recurevite(mat1, &RES1);
            }





            timetoChar(departingTime - endTime, TIME);
            //SDL_FreeSurface(timeleft);
            timeleft =TTF_RenderText_Blended(police,TIME, noir);
            sprintf(Cscore, "%d", RES1);

            //SDL_FreeSurface(Score);
            Score = TTF_RenderText_Blended(police, Cscore, noir);
            sprintf(Cscore, "%d", RES2);
            score2 = TTF_RenderText_Blended(police, Cscore, noir);




                /** les blits **/
            SDL_FillRect(ecran2, NULL, SDL_MapRGB(ecran2->format, 100,150,200));
            pos.x = 0;
            pos.y = 0;
            //SDL_BlitSurface(background, NULL, ecran2, &pos);

                pos.x = timeX2;
                pos.y = timeY2;
                SDL_BlitSurface(time, NULL, ecran2, &pos);
                pos.y += 50;
                SDL_BlitSurface(timeleft, NULL, ecran2, &pos);
                pos.x = Xscore2;
                pos.y = Yscore2;
                SDL_BlitSurface(scoreText, NULL, ecran2, &pos);
                pos.y += 30;
                SDL_BlitSurface(Score, NULL, ecran2, &pos);
                pos.x += 200;
                SDL_BlitSurface(score2, NULL, ecran2, &pos);
                pos.x = Xpause2;
                pos.y = Ypause2;
                SDL_BlitSurface(bouton, NULL, ecran2, &pos);
                pos.x = Xarret2;
                pos.y = Yarret2;
                SDL_BlitSurface(arretB, NULL, ecran2, &pos);
                if(etape > 0)
                    {
                        pos.x = Xcanvas2 + LARGEUR_CELLULE * a;
                        pos.y = Ycanvas2 + HAUTEUR_CELLULE * b;
                        SDL_BlitSurface(shade, NULL, ecran2, &pos);
                    }
                if(etape > 1 )
                {
                    pos.x = Xcanvas2 + LARGEUR_CELLULE * c;
                    pos.y = Ycanvas2 + HAUTEUR_CELLULE * d;
                    SDL_BlitSurface(shade2, NULL, ecran2, &pos);
                }
                if(etape2 == 2)
                {
                    pos.x = Xcanvas3 + LARGEUR_CELLULE * w;
                    pos.y = Ycanvas3 + HAUTEUR_CELLULE * x;
                    SDL_BlitSurface(shade, NULL, ecran2, &pos);
                    pos.x = Xcanvas3 + LARGEUR_CELLULE * y;
                    pos.y = Ycanvas3 + HAUTEUR_CELLULE * z;
                    SDL_BlitSurface(shade2, NULL, ecran2, &pos);
                }

                for(i = 0; i< 10; i++)
                {
                    for(j= 0; j< 11; j++)
                    {
                        pos.x = Xcanvas2 + LARGEUR_CELLULE * j;
                        pos.y = Ycanvas2 + HAUTEUR_CELLULE * i;
                        switch(mat1[i][j])
                        {
                        case 0:
                            SDL_BlitSurface(gryffondor, NULL, ecran2, &pos);
                            break;
                        case 1:
                            SDL_BlitSurface(hufflepuff, NULL, ecran2, &pos);
                            break;
                            case 2:
                            SDL_BlitSurface(ravenclaw, NULL, ecran2, &pos);
                            break;
                        case 3:
                            SDL_BlitSurface(slytherin, NULL, ecran2, &pos);
                            break;
                        case 4:
                            SDL_BlitSurface(ministry, NULL, ecran2, &pos);
                            break;
                        case 5:
                            SDL_BlitSurface(sword, NULL, ecran2, &pos);
                            break;
                        case 6:
                            SDL_BlitSurface(cup, NULL, ecran2, &pos);
                            break;
                        case 7:
                            SDL_BlitSurface(tiarra, NULL, ecran2, &pos);
                            break;
                        case 8:
                            SDL_BlitSurface(locket, NULL, ecran2, &pos);
                            break;
                        case 9:
                            SDL_BlitSurface(de, NULL, ecran2, &pos);
                            break;
                         case 10:
                            SDL_BlitSurface(houses, NULL, ecran2, &pos);
                            break;
                        }
                    }
                }
                for(i = 0; i< 10; i++)
                {
                    for(j= 0; j< 11; j++)
                    {
                        pos.x = Xcanvas3 + LARGEUR_CELLULE * j;
                        pos.y = Ycanvas3 + HAUTEUR_CELLULE * i;
                        switch(mat2[i][j])
                        {
                        case 0:
                            SDL_BlitSurface(gryffondor, NULL, ecran2, &pos);
                            break;
                        case 1:
                            SDL_BlitSurface(hufflepuff, NULL, ecran2, &pos);
                            break;
                            case 2:
                            SDL_BlitSurface(ravenclaw, NULL, ecran2, &pos);
                            break;
                        case 3:
                            SDL_BlitSurface(slytherin, NULL, ecran2, &pos);
                            break;
                        case 4:
                            SDL_BlitSurface(ministry, NULL, ecran2, &pos);
                            break;
                        case 5:
                            SDL_BlitSurface(sword, NULL, ecran2, &pos);
                            break;
                        case 6:
                            SDL_BlitSurface(cup, NULL, ecran2, &pos);
                            break;
                        case 7:
                            SDL_BlitSurface(tiarra, NULL, ecran2, &pos);
                            break;
                        case 8:
                            SDL_BlitSurface(locket, NULL, ecran2, &pos);
                            break;
                        case 9:
                            SDL_BlitSurface(de, NULL, ecran2, &pos);
                            break;
                         case 10:
                            SDL_BlitSurface(houses, NULL, ecran2, &pos);
                            break;
                        }
                    }
                }
                if(etape2 == 2)
                    etape2 = 0;
                SDL_Flip(ecran2);
                startTime = endTime;
            }
            else
            {
                SDL_Delay(500- (endTime - startTime));
            }


        }
        SDL_FreeSurface(background);
        SDL_FreeSurface(shade2);
        SDL_FreeSurface(timeleft);
        SDL_FreeSurface(time);
        SDL_FreeSurface(shade);
        SDL_FreeSurface(gryffondor);
        SDL_FreeSurface(hufflepuff);
        SDL_FreeSurface(ravenclaw);
        SDL_FreeSurface(slytherin);
        SDL_FreeSurface(ministry);
        SDL_FreeSurface(sword);
        SDL_FreeSurface(tiarra);
        SDL_FreeSurface(cup);
        SDL_FreeSurface(locket);
        SDL_FreeSurface(de);
        SDL_FreeSurface(houses);
        SDL_FreeSurface(scoreText);
        SDL_FreeSurface(Score);
        SDL_FreeSurface(score2);
        SDL_FreeSurface(time);
        SDL_FreeSurface(timeleft);
        SDL_FreeSurface(boutonhelp);
        SDL_FreeSurface(bouton);
        SDL_FreeSurface(arretB);
        SDL_FreeSurface(ecran2);
        SDL_Quit();
}
