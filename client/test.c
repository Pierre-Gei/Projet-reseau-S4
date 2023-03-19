#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "conversion.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "structure.h"

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
    int r, g, b;
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


int main() 
{
    CU_initialize_registry();
    SDL_ColorRect colorRect;
    colorRect.color.r = 0;
    colorRect.color.g = 0;
    colorRect.color.b = 0;
    colorRect.color.a = 0;
    colorRect.rect.x = 0;
    colorRect.rect.y = 0;
    colorRect.rect.w = 0;
    colorRect.rect.h = 0;
    printf ( "%d %d %d %d %d %d %d %d", colorRect.color.r, colorRect.color.g, colorRect.color.b, colorRect.color.a, colorRect.rect.x, colorRect.rect.y, colorRect.rect.w, colorRect.rect.h);

    CU_pSuite suite_test_convert_RGB_BASE_64 = CU_add_suite("convert_RGB_BASE_64", NULL, NULL);
    CU_add_test(suite_test_convert_RGB_BASE_64, "test_convert_RGB_BASE_64", test_convert_RGB_BASE_64);

    CU_pSuite suite_test_convert_BASE_64_RGB = CU_add_suite("convert_BASE_64_RGB", NULL, NULL);
    CU_add_test(suite_test_convert_BASE_64_RGB, "test_convert_BASE_64_RGB", test_convert_BASE_64_RGB);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}