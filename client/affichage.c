#include <stdio.h>
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

CASE initCase(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h)
{
    CASE c;
    c.color.r = r;
    c.color.g = g;
    c.color.b = b;
    c.color.a = a;
    c.rect.x = x;
    c.rect.y = y;
    c.rect.w = w;
    c.rect.h = h;
    return c;
}

void initTabCases(CASE cases[])
{
    int cote = 75;
    cases[0] = initCase(0, 0, 0, 255, 0, 0, cote, cote); //black
    cases[1] = initCase(128, 128, 128, 255, 0, 0, cote, cote); //grey
    cases[2] = initCase(255, 255, 255, 255, 0, 0, cote, cote); //white
    cases[3] = initCase(165, 42, 42, 255, 0, 0, cote, cote); //brown
    cases[4] = initCase(255, 0, 0, 255, 0, 0, cote, cote); //red  
    cases[5] = initCase(255, 165, 0, 255, 0, 0, cote, cote); //orange
    cases[6] = initCase(255, 255, 0, 255, 0, 0, cote, cote); //yellow 
    cases[7] = initCase(0, 255, 0, 255, 0, 0, cote, cote); //green
    cases[8] = initCase(50, 205, 50, 255, 0, 0, cote, cote); //lime
    cases[9] = initCase(0, 255, 255, 255, 0, 0, cote, cote); //cyan
    cases[10] = initCase(0, 0, 255, 255, 0, 0, cote, cote); //blue
    cases[11] = initCase(128, 0, 128, 255, 0, 0, cote, cote); //purple
    cases[12] = initCase(255, 0, 255, 255, 0, 0, cote, cote); //magenta
    cases[13] = initCase(255, 192, 203, 255, 0, 0, cote, cote); //pink 
}

void color_picker(SDL_Renderer *renderer, int width_screen, int height_screen, char *MessageEnvoi, CASE cases[], int size_cases)
{
    int x = (width_screen - 7 * cases[0].rect.h) / 2;
    int y = height_screen - 2 * cases[0].rect.h;
    for (int i = 0; i < size_cases; i++)
    {
        cases[i].rect.x = x;
        cases[i].rect.y = y;
        SDL_SetRenderDrawColor(renderer, cases[i].color.r, cases[i].color.g, cases[i].color.b, cases[i].color.a);
        SDL_RenderFillRect(renderer, &cases[i].rect);
        SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255);
        SDL_RenderDrawRect(renderer, &cases[i].rect);
        x += cases[0].rect.h;
        if (i == 6)
        {
            x = (width_screen - 7 * cases[0].rect.h) / 2;
            y += cases[0].rect.h;
        }
    }
}

int min (int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void position_case_matrix(int width_screen, int height_screen, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth])
{
    int cote = min(width_screen / MatrixWidth, height_screen / MatrixHeight);
    int x = (width_screen - MatrixWidth * cote) / 2;
    int y = (height_screen - MatrixHeight * cote) / 2;
    for (int i = 0; i < MatrixHeight; i++)
    {
        for (int j = 0; j < MatrixWidth; j++)
        {
            colorRect[i][j].rect.x = x + j * cote;
            colorRect[i][j].rect.y = y + i * cote;
            colorRect[i][j].rect.w = cote;
            colorRect[i][j].rect.h = cote;
        }
    }
}

void draw_matrix(SDL_Renderer *renderer, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth])
{
    for (int i = 0; i < MatrixHeight; i++)
    {
        for (int j = 0; j < MatrixWidth; j++)
        {
            SDL_SetRenderDrawColor(renderer, colorRect[i][j].color.r, colorRect[i][j].color.g, colorRect[i][j].color.b, colorRect[i][j].color.a);
            SDL_RenderFillRect(renderer, &colorRect[i][j].rect);
            SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255);
            SDL_RenderDrawRect(renderer, &colorRect[i][j].rect);
        }
    }
}