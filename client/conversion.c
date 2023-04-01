#include <string.h>
#include <SDL2/SDL.h>
#include "structure.h"

#define lenght_base64 4
#define BASE_64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void convert_BASE_64_RGB(char *base64, Uint8 *r, Uint8 *g, Uint8 *b)
{
    int i;
    int rgb = 0;
    for (i = 0; i < lenght_base64; i++)
    {
        rgb <<= 6;
        rgb += strchr(BASE_64, base64[i]) - BASE_64;
    }
    *r = (rgb >> 16) & 0xFF;
    *g = (rgb >> 8) & 0xFF;
    *b = rgb & 0xFF;
}


void separate_string(char string[], int size, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth])
{
    char tab[5]; 
    memset(tab, 0, sizeof(tab));
    for (int i = 0; i < MatrixHeight; i++)
    {
        for (int j = 0; j < MatrixWidth; j++)
        {
            for (int k = 0; k < lenght_base64; k++)
            {
                tab[k] = string[i * MatrixWidth * lenght_base64 + j * lenght_base64 + k];
            }
            convert_BASE_64_RGB(tab, &colorRect[i][j].color.r, &colorRect[i][j].color.g, &colorRect[i][j].color.b);
            colorRect[i][j].color.a = 255;
            memset(tab, 0, sizeof(tab));
        }
    }
}

void convert_RGB_BASE_64(int r, int g, int b, char *base64)
{
    int i;
    int rgb = (r << 16) + (g << 8) + b;
    for (i = 0; i < lenght_base64; i++)
    {
        base64[i] = BASE_64[rgb & 0x3F];
        rgb >>= 6;
    }
    base64[lenght_base64] = '\0';
    for (i = 0; i < lenght_base64 / 2; i++)
    {
        char temp = base64[i];
        base64[i] = base64[lenght_base64 - i - 1];
        base64[lenght_base64 - i - 1] = temp;
    }
}


