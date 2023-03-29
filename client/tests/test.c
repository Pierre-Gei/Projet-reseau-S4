#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "../structure.h"
#include "../conversion.h"
#include "test_affichage.h"
#include "test_conversion.h"
#include "test_liaison.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


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