#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


Matrix initMatrix(Matrix m)
{
    m.width = 0;
    m.height = 0;
    m.pixel_min = 0;
    m.pixels = NULL;
    return m;
}

Matrix initPixelsMatrix(Matrix m, int width, int height)
{
    int i, j;
    m.width = width;
    m.height = height;
    m.pixel_min = 0;
    m.pixels = (char **)malloc(sizeof(char *) * height);
    for (i = 0; i < height; i++)
    {
        m.pixels[i] = (char *)malloc(sizeof(char) * width);
        for (j = 0; j < width; j++)
        {
            m.pixels[i][j] = '////';
        }
    }
    return m;
}

//free the matrix
void freeMatrix(Matrix m)
{
    int i;
    for (i = 0; i < m.height; i++)
    {
        free(m.pixels[i]);
    }
    free(m.pixels);
}