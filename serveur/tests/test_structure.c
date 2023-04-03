#include <string.h>
#include <time.h>
#include "../structure.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_initMatrix() 
{
    // Créer une matrice vide
    Matrix m;
    m = initMatrix(m);

    // Vérifier que les attributs ont été initialisés correctement
    CU_ASSERT_EQUAL(m.width, 0);
    CU_ASSERT_EQUAL(m.height, 0);
    CU_ASSERT_EQUAL(m.pixel_min, 0);
    CU_ASSERT_EQUAL(m.pixels, NULL);

    // Créer une matrice avec des pixels
    int width = 2;
    int height = 2;
    int pixel_min = 0;
    char *pixels[2][2] = {{"red", "blue"}, {"green", "yellow"}};
    Matrix m2 = {width, height, pixel_min, (char ***)pixels};
    m2 = initMatrix(m2);

    // Vérifier que les attributs ont été initialisés correctement
    CU_ASSERT_EQUAL(m2.width, 0);
    CU_ASSERT_EQUAL(m2.height, 0);
    CU_ASSERT_EQUAL(m2.pixel_min, 0);
    CU_ASSERT_EQUAL(m2.pixels, NULL);
}

void test_initPixelsMatrix()
{
    Matrix m;
    m.width = 3;
    m.height = 2;
    m.pixel_min = 0;
    initPixelsMatrix(&m);

    // Vérifier que la matrice a bien été initialisée
    CU_ASSERT_EQUAL(m.width, 3);
    CU_ASSERT_EQUAL(m.height, 2);
    CU_ASSERT_EQUAL(m.pixel_min, 0);
    CU_ASSERT_PTR_NOT_NULL(m.pixels);

    // Vérifier que chaque pixel a bien été initialisé à "////"
    int i, j;
    for (i = 0; i < m.height; i++)
    {
        for (j = 0; j < m.width; j++)
        {
            CU_ASSERT_STRING_EQUAL(m.pixels[i][j], "////");
        }
    }

    // // Libérer la mémoire allouée
    // freePixelsMatrix(&m);
}

void test_freeMatrix()
{
    // Créer une matrice avec des pixels initialisés
    Matrix m;
    m.width = 2;
    m.height = 2;
    m.pixel_min = 0;
    initPixelsMatrix(&m);

    // Appeler la fonction à tester
    freeMatrix(m);

    // Vérifier que la matrice est vide après avoir été libérée
    CU_ASSERT_EQUAL(m.pixels, NULL);
}

