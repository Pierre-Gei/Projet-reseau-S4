#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <time.h>

#include "../structure.h"
#include "../matrices.h"
#include "../traitement.h"
#include "test_user.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


void test_timeOut() 
{
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

void test_reallocPoll() 
{
    // Création d'un tableau de test
    struct pollfd *tabPoll = malloc(2 * sizeof(struct pollfd));
    tabPoll[0].fd = 1;
    tabPoll[0].events = POLLIN;
    tabPoll[1].fd = 2;
    tabPoll[1].events = POLLOUT;

    // Création d'une liste d'utilisateurs pour le test
    User user1 = { .socketClient = 3 };
    User user2 = { .socketClient = 4 };
    user1.suivant = &user2;
    user2.suivant = NULL;

    // Taille initiale du tableau
    int size = 2;

    // Appel de la fonction à tester
    tabPoll = reallocPoll(tabPoll, &user1, 5, &size);

    // Vérification du résultat
    CU_ASSERT_EQUAL(tabPoll[0].fd, 5);
    CU_ASSERT_EQUAL(tabPoll[0].events, POLLIN);
    CU_ASSERT_EQUAL(tabPoll[1].fd, 3);
    CU_ASSERT_EQUAL(tabPoll[1].events, POLLIN);
    CU_ASSERT_EQUAL(tabPoll[2].fd, 4);
    CU_ASSERT_EQUAL(tabPoll[2].events, POLLIN);

    // Nettoyage de la mémoire allouée
    free(tabPoll);
}
