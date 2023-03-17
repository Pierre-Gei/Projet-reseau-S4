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

#include "structure.h"
#include "matrices.h"
#include "fonctions.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


void test_timeOut() {
    Matrix matrix = {10};
    User user;
    user.pixel = 10;
    user.time = time(NULL) - 61;
    user.precedent = NULL;
    user.suivant = NULL;
    user.socketClient = 0;
    timeOut(&user, &matrix);
    CU_ASSERT_EQUAL(user.pixel, 10);

    user.pixel = 5;
    user.time = time(NULL);
    timeOut(&user, &matrix);
    CU_ASSERT_EQUAL(user.pixel, 5);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("timeOut", NULL, NULL);
    CU_add_test(suite, "test_timeOut", test_timeOut);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}