#include <string.h>
#include "../structure.h"
#include "../conversion.h"
#include "test_affichage.h"
#include "test_conversion.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


int main() 
{
    CU_initialize_registry();

    CU_pSuite suite_test_convert_RGB_BASE_64 = CU_add_suite("convert_RGB_BASE_64", NULL, NULL);
    CU_add_test(suite_test_convert_RGB_BASE_64, "test_convert_RGB_BASE_64", test_convert_RGB_BASE_64);

    CU_pSuite suite_test_convert_BASE_64_RGB = CU_add_suite("convert_BASE_64_RGB", NULL, NULL);
    CU_add_test(suite_test_convert_BASE_64_RGB, "test_convert_BASE_64_RGB", test_convert_BASE_64_RGB);

    CU_pSuite suite_test_separate_string = CU_add_suite("separate_string", NULL, NULL);
    CU_add_test(suite_test_separate_string, "test_separate_string", test_separate_string);

    CU_pSuite suite_test_init = CU_add_suite("init", NULL, NULL);
    CU_add_test(suite_test_init, "test_init", test_init);

    CU_pSuite suite_test_initCase = CU_add_suite("initCase", NULL, NULL);
    CU_add_test(suite_test_initCase, "test_initCase", test_initCase);

    CU_pSuite suite_test_min = CU_add_suite("min", NULL, NULL);
    CU_add_test(suite_test_min, "test_min", test_min);
    
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}