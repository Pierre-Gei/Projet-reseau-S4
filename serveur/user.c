#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include "structure.h"

void addUser(User **userList, int socketClient, struct sockaddr_in *sockin)
{
    User *newUser = malloc(sizeof(User));
    newUser->socketClient = socketClient;
    newUser->sockin = malloc(sizeof(struct sockaddr_in));
    memcpy(newUser->sockin, sockin, sizeof(struct sockaddr_in));
    newUser->suivant = NULL;
    newUser->precedent = NULL;
    if (*userList == NULL)
    {
        *userList = newUser;
    }
    else
    {
        User *tmp = *userList;
        while (tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = newUser;
        newUser->precedent = tmp;
    }
}

void deleteUser(User **userList, User *user)
{
    if (user->precedent == NULL)
    {
        *userList = user->suivant;
    }
    else
    {
        user->precedent->suivant = user->suivant;
    }
    if (user->suivant != NULL)
    {
        user->suivant->precedent = user->precedent;
    }
    free(user);
}

User *findUserBySocket(User *userList, int socket)
{
    User *tmp = userList;
    while (tmp != NULL)
    {
        if (tmp->socketClient == socket)
        {
            return tmp;
        }
        tmp = tmp->suivant;
    }
    return NULL;
}

void freeUserList(User *userList)
{
    User *tmp = userList;
    while (tmp != NULL)
    {
        userList = userList->suivant;
        free(tmp);
        tmp = userList;
    }
}