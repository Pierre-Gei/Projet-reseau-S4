#include <string.h>
#include <time.h>
#include "../structure.h"
#include "../matrices.h"

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