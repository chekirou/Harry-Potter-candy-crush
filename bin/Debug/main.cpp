#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "constantes.h"
#include "mechanique.h"
#include "mechanique.c"
#include "jeu.h"
#include "jeu.c"
int main(int argc, char *argv[])
{
        SDL_Surface *ecran = NULL, *menu = NULL, *boutonnormal = NULL, *boutonsaved = NULL;
        SDL_Rect postionmenu, posplay;

        SDL_Event event;

        int continuer = 1;
        SDL_Init(SDL_INIT_VIDEO);
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);
        SDL_WM_SetCaption("magic crush", NULL);
        postionmenu.x = 0;
        postionmenu.y = 0;
        posplay.x = 507;
        posplay.y = 223;
        menu = IMG_Load("hogwartswall.jpg");
        boutonsaved = IMG_Load("boutonsaved.png");
        boutonnormal = IMG_Load("boutonPlay1.png");
        srand(time(NULL));
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
                else if(event.key.keysym.sym ==SDLK_SPACE )
                    {humainMachine();}

                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.x > 507 && event.button.x < 682 && event.button.y > 223 && event.button.y <299 )
                {

                    jouer(ecran, 0);
                }
                if(event.button.x > 507 && event.button.x < 682 && event.button.y > 323 && event.button.y <399 )
                {

                    jouer(ecran, 1);
                }
                break;


            }
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));
            SDL_BlitSurface(menu, NULL, ecran, &postionmenu);
            posplay.x = 507;
            posplay.y = 223;
            SDL_BlitSurface(boutonnormal, NULL, ecran, &posplay);
            posplay.y += 100;
            SDL_BlitSurface(boutonsaved, NULL, ecran, &posplay);
            SDL_Flip(ecran);

        }
        SDL_FreeSurface(menu);
        SDL_FreeSurface(boutonnormal);
         SDL_FreeSurface(boutonsaved);
        SDL_Quit();
        return EXIT_SUCCESS;

}
