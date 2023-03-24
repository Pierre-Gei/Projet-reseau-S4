#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "structure.h"

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de la SDL: %s", SDL_GetError());
        return -1;
    }
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer) != 0)
    {
        printf("Erreur lors de la creation de la fenetre et du renderer: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

void color_picker(SDL_Renderer *renderer, int width_screen, int height_screen, char *MessageEnvoi)
{
    SDL_Event event;
    int cote = 75;
    printf("width_screen = %d\n", width_screen);

    CASE red = {{255, 0, 0, 255}, {0, 0, cote, cote}};
    CASE green = {{0, 255, 0, 255}, {0, 0, cote, cote}};
    CASE blue = {{0, 0, 255, 255}, {0, 0, cote, cote}};
    CASE white = {{255, 255, 255, 255}, {0, 0, cote, cote}};
    CASE black = {{0, 0, 0, 255}, {0, 0, cote, cote}};
    CASE yellow = {{255, 255, 0, 255}, {0, 0, cote, cote}};
    CASE orange = {{255, 165, 0, 255}, {0, 0, cote, cote}};
    CASE purple = {{128, 0, 128, 255}, {0, 0, cote, cote}};
    CASE pink = {{255, 192, 203, 255}, {0, 0, cote, cote}};
    CASE brown = {{165, 42, 42, 255}, {0, 0, cote, cote}};
    CASE grey = {{128, 128, 128, 255}, {0, 0, cote, cote}};
    CASE cyan = {{0, 255, 255, 255}, {0, 0, cote, cote}};
    CASE magenta = {{255, 0, 255, 255}, {0, 0, cote, cote}};
    CASE lime = {{50, 205, 50, 255}, {0, 0, cote, cote}};

    CASE *cases[14] = {&red, &green, &blue, &white, &black, &yellow, &orange, &purple, &pink, &brown, &grey, &cyan, &magenta, &lime};
    //C'est en bas de l'écran, centré horizontalement et les cases sont sur 2 lignes de 7 cases
    int x = (width_screen - 7 * cote) / 2;
    int y = height_screen - 2 * cote;
    for (int i = 0; i < 14; i++)
    {
        cases[i]->rect.x = x;
        cases[i]->rect.y = y;
        SDL_SetRenderDrawColor(renderer, cases[i]->color.r, cases[i]->color.g, cases[i]->color.b, cases[i]->color.a);
        SDL_RenderFillRect(renderer, &cases[i]->rect);
        x += cote;
        if (i == 6)
        {
            x = (width_screen - 7 * cote) / 2;
            y += cote;
        }
    }
}