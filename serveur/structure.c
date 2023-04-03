#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"

Matrix initMatrix(Matrix m)
{
    m.width = 0;
    m.height = 0;
    m.pixel_min = 0;
    m.pixels = NULL;
    return m;
}

void initPixelsMatrix(Matrix *m)
{
    int i, j;
    m->pixels = (char ***)malloc(sizeof(char **) * m->height);
    for (i = 0; i < m->height; i++)
    {
        m->pixels[i] = (char **)malloc(sizeof(char *) * m->width);
    }
    for (i = 0; i < m->height; i++)
    {
        for (j = 0; j < m->width; j++)
        {
            m->pixels[i][j] = (char *)malloc(sizeof(char) * 4);
            memcpy(m->pixels[i][j], "////", 4);
        }
    }
}

// free the matrix //////////////////////// a tester
void freeMatrix(Matrix m)
{
    int i, j;
    for (i = 0; i < m.height; i++)
    {
        for (j = 0; j < m.width; j++)
        {
            free(m.pixels[i][j]);
        }
        free(m.pixels[i]);
    }
    free(m.pixels);
}