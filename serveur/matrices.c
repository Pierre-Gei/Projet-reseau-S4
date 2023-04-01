#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"

#define lenght_base64 4
#define BASE_64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

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

void convert_BASE_64_RGB(char *base64, int *r, int *g, int *b)
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

int verif_BASE_64(char *base64)
{
    int i,r,g,b;
    int rgb = 0;
    if (strlen(base64)>4)
    {
        return 1;
    }
    for (i = 0; i < lenght_base64; i++)
    {
        rgb <<= 6;
        rgb += strchr(BASE_64, base64[i]) - BASE_64;
    }
    r = (rgb >> 16) & 0xFF;
    g = (rgb >> 8) & 0xFF;
    b = rgb & 0xFF;
    if (r>255 || r<0)
    {
        return 1;
    }
    else if (b>255 || b<0)
    {
        return 1;
    }
    else if (g>255 || g<0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

//add change a pixel in the matrix
void editPixel(Matrix m, int x, int y, char *base64){
    if (x >= 0 && x < m.width && y >= 0 && y < m.height)
    {
        strcpy(m.pixels[y][x], base64);
    }
}

void printMatrix(Matrix m)
{
    int i, j;
    for (i = 0; i < m.height; i++)
    {
        for (j = 0; j < m.width; j++)
        {
            printf("[%s] ", m.pixels[i][j]);
        }
    }
}