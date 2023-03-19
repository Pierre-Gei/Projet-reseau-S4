#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <time.h>
#include "test_user.h"
#include "test_fonctions.h"
#include "test_structure.h"
#include "test_matrices.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int main() {
    CU_initialize_registry();

    CU_pSuite suite_timout = CU_add_suite("timeOut", NULL, NULL);
    CU_add_test(suite_timout, "test_timeOut", test_timeOut);

    CU_pSuite suite_reallocPoll = CU_add_suite("reallocPoll", NULL, NULL);
    CU_add_test(suite_reallocPoll, "test_reallocPoll", test_reallocPoll);

    CU_pSuite suite_addUser = CU_add_suite("addUser", NULL, NULL);
    CU_add_test(suite_addUser, "test_addUser", test_addUser);

    CU_pSuite suite_deleteUser = CU_add_suite("deleteUser", NULL, NULL);
    CU_add_test(suite_deleteUser, "test_deleteUser", test_deleteUser);

    CU_pSuite suite_findUserBySocket = CU_add_suite("findUserBySocket", NULL, NULL);
    CU_add_test(suite_findUserBySocket, "test_findUserBySocket", test_findUserBySocket);

    CU_pSuite suite_initMatrix = CU_add_suite("initMatrix", NULL, NULL);
    CU_add_test(suite_initMatrix, "test_initMatrix", test_initMatrix);

    CU_pSuite suite_initPixelsMatrix = CU_add_suite("initPixelsMatrix", NULL, NULL);
    CU_add_test(suite_initPixelsMatrix, "test_initPixelsMatrix", test_initPixelsMatrix);

    // CU_pSuite suite_freeMatrix = CU_add_suite("freeMatrix", NULL, NULL); ////echec
    // CU_add_test(suite_freeMatrix, "test_freeMatrix", test_freeMatrix);

    CU_pSuite suite_test_convert_RGB_BASE_64 = CU_add_suite("convert_RGB_BASE_64", NULL, NULL);
    CU_add_test(suite_test_convert_RGB_BASE_64, "test_convert_RGB_BASE_64", test_convert_RGB_BASE_64);

    CU_pSuite suite_test_convert_BASE_64_RGB = CU_add_suite("convert_BASE_64_RGB", NULL, NULL);
    CU_add_test(suite_test_convert_BASE_64_RGB, "test_convert_BASE_64_RGB", test_convert_BASE_64_RGB);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}