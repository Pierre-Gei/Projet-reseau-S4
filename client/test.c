#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "structure.h"
#include "conversion.h"
#include "affichage.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define lenght_base64 4
#define BASE_64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"



void test_convert_RGB_BASE_64()
{
    char base64[lenght_base64 + 1];
    convert_RGB_BASE_64(255, 255, 255, base64);
    CU_ASSERT_STRING_EQUAL(base64, "////");

    convert_RGB_BASE_64(255, 0, 0, base64);
    CU_ASSERT_STRING_EQUAL(base64, "/wAA");

    convert_RGB_BASE_64(0, 255, 0, base64);
    CU_ASSERT_STRING_EQUAL(base64, "AP8A");

    convert_RGB_BASE_64(0, 0, 255, base64);
    CU_ASSERT_STRING_EQUAL(base64, "AAD/");

    convert_RGB_BASE_64(0, 0, 0, base64);
    CU_ASSERT_STRING_EQUAL(base64, "AAAA");
}

void test_convert_BASE_64_RGB()
{
    Uint8 r, g, b;
    convert_BASE_64_RGB("////", &r, &g, &b);
    CU_ASSERT_EQUAL(r, 255);
    CU_ASSERT_EQUAL(g, 255);
    CU_ASSERT_EQUAL(b, 255);

    convert_BASE_64_RGB("/wAA", &r, &g, &b);
    CU_ASSERT_EQUAL(r, 255);
    CU_ASSERT_EQUAL(g, 0);
    CU_ASSERT_EQUAL(b, 0);

    convert_BASE_64_RGB("AP8A", &r, &g, &b);
    CU_ASSERT_EQUAL(r, 0);
    CU_ASSERT_EQUAL(g, 255);
    CU_ASSERT_EQUAL(b, 0);

    convert_BASE_64_RGB("AAD/", &r, &g, &b);
    CU_ASSERT_EQUAL(r, 0);
    CU_ASSERT_EQUAL(g, 0);
    CU_ASSERT_EQUAL(b, 255);

    convert_BASE_64_RGB("AAAA", &r, &g, &b);
    CU_ASSERT_EQUAL(r, 0);
    CU_ASSERT_EQUAL(g, 0);
    CU_ASSERT_EQUAL(b, 0);
}

void test_separate_string()
{
    char string[] = "AAD/////////////AP8A////";
    int size = strlen(string);
    int width = 3;
    int height = 2;
    CASE colorRect[height][width];
    separate_string(string, size, width, height,100,100, colorRect);
    CU_ASSERT_EQUAL(colorRect[0][0].color.r, 0);
    CU_ASSERT_EQUAL(colorRect[0][0].color.g, 0);
    CU_ASSERT_EQUAL(colorRect[0][0].color.b, 255);
    CU_ASSERT_EQUAL(colorRect[0][1].color.r, 255);
    CU_ASSERT_EQUAL(colorRect[0][1].color.g, 255);
    CU_ASSERT_EQUAL(colorRect[0][1].color.b, 255);
    CU_ASSERT_EQUAL(colorRect[0][2].color.r, 255);
    CU_ASSERT_EQUAL(colorRect[0][2].color.g, 255);
    CU_ASSERT_EQUAL(colorRect[0][2].color.b, 255);
    CU_ASSERT_EQUAL(colorRect[1][0].color.r, 255);
    CU_ASSERT_EQUAL(colorRect[1][0].color.g, 255);
    CU_ASSERT_EQUAL(colorRect[1][0].color.b, 255);
    CU_ASSERT_EQUAL(colorRect[1][1].color.r, 0);
    CU_ASSERT_EQUAL(colorRect[1][1].color.g, 255);
    CU_ASSERT_EQUAL(colorRect[1][1].color.b, 0);
    CU_ASSERT_EQUAL(colorRect[1][2].color.r, 255);
    CU_ASSERT_EQUAL(colorRect[1][2].color.g, 255);
    CU_ASSERT_EQUAL(colorRect[1][2].color.b, 255);
}


int main() 
{
    CU_initialize_registry();
    CASE colorRect [2][2];
    

    CU_pSuite suite_test_convert_RGB_BASE_64 = CU_add_suite("convert_RGB_BASE_64", NULL, NULL);
    CU_add_test(suite_test_convert_RGB_BASE_64, "test_convert_RGB_BASE_64", test_convert_RGB_BASE_64);

    CU_pSuite suite_test_convert_BASE_64_RGB = CU_add_suite("convert_BASE_64_RGB", NULL, NULL);
    CU_add_test(suite_test_convert_BASE_64_RGB, "test_convert_BASE_64_RGB", test_convert_BASE_64_RGB);

    CU_pSuite suite_test_separate_string = CU_add_suite("separate_string", NULL, NULL);
    CU_add_test(suite_test_separate_string, "test_separate_string", test_separate_string);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}