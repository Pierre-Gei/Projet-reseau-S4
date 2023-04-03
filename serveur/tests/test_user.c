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

#include "../structure.h"
#include "../user.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_addUser()
{
    // On crée une liste d'utilisateurs vide
    User *userList = NULL;

    // On ajoute un utilisateur à la liste
    int socketClient = 42;
    struct sockaddr_in sockin;
    int pixel = 0;
    addUser(&userList, socketClient, &sockin, pixel,0);

    // On vérifie que la liste contient un seul utilisateur
    CU_ASSERT_PTR_NOT_NULL(userList);
    CU_ASSERT_PTR_NULL(userList->precedent);
    CU_ASSERT_PTR_NULL(userList->suivant);
    CU_ASSERT_EQUAL(userList->socketClient, socketClient);
    CU_ASSERT_EQUAL(userList->pixel, pixel);
    CU_ASSERT_EQUAL(userList->time, 0);

    // On ajoute un deuxième utilisateur à la liste
    int socketClient2 = 43;
    struct sockaddr_in sockin2;
    int pixel2 = 1;
    addUser(&userList, socketClient2, &sockin2, pixel2, 0);

    // On vérifie que la liste contient deux utilisateurs
    CU_ASSERT_PTR_NOT_NULL(userList);
    CU_ASSERT_PTR_NULL(userList->precedent);
    CU_ASSERT_PTR_NOT_NULL(userList->suivant);
    CU_ASSERT_PTR_NULL(userList->suivant->suivant);
    CU_ASSERT_EQUAL(userList->socketClient, socketClient);
    CU_ASSERT_EQUAL(userList->pixel, pixel);
    CU_ASSERT_EQUAL(userList->time, 0);
    CU_ASSERT_EQUAL(userList->suivant->socketClient, socketClient2);
    CU_ASSERT_EQUAL(userList->suivant->pixel, pixel2);
    CU_ASSERT_EQUAL(userList->suivant->time, 0);
}

void test_deleteUser()
{
    // On crée une liste d'utilisateurs avec deux utilisateurs
    User *userList = NULL;
    int socketClient1 = 42;
    struct sockaddr_in sockin1;
    int pixel1 = 0;
    addUser(&userList, socketClient1, &sockin1, pixel1,0);
    int socketClient2 = 43;
    struct sockaddr_in sockin2;
    int pixel2 = 1;
    addUser(&userList, socketClient2, &sockin2, pixel2,0);

    // On supprime le deuxième utilisateur de la liste
    deleteUser(&userList, userList->suivant);

    // On vérifie que la liste ne contient plus que le premier utilisateur
    CU_ASSERT_PTR_NOT_NULL(userList);
    CU_ASSERT_PTR_NULL(userList->precedent);
    CU_ASSERT_PTR_NULL(userList->suivant);
    CU_ASSERT_EQUAL(userList->socketClient, socketClient1);
    CU_ASSERT_EQUAL(userList->pixel, pixel1);
    CU_ASSERT_EQUAL(userList->time, 0);

    // On supprime le premier utilisateur de la liste
    deleteUser(&userList, userList);

    // On vérifie que la liste est vide
    CU_ASSERT_PTR_NULL(userList);
}

void test_findUserBySocket()
{
    // Création d'une liste d'utilisateurs avec des sockets clients différents
    User *user1 = malloc(sizeof(User));
    user1->socketClient = 1;
    user1->suivant = NULL;

    User *user2 = malloc(sizeof(User));
    user2->socketClient = 2;
    user2->suivant = NULL;
    user1->suivant = user2;

    User *user3 = malloc(sizeof(User));
    user3->socketClient = 3;
    user3->suivant = NULL;
    user2->suivant = user3;

    // Test avec un utilisateur présent dans la liste
    User *result = findUserBySocket(user1, 2);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->socketClient, 2);

    // Test avec un utilisateur non présent dans la liste
    result = findUserBySocket(user1, 4);
    CU_ASSERT_PTR_NULL(result);

    // Libération de la mémoire allouée
    free(user1);
    free(user2);
    free(user3);
}

