#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "structure.h"

void addUser(User **userList, int socketClient, struct sockaddr_in *sockin, int pixel, time_t time)
{
    User *newUser = malloc(sizeof(User));
    newUser->socketClient = socketClient;
    newUser->sockin = malloc(sizeof(struct sockaddr_in));
    memcpy(newUser->sockin, sockin, sizeof(struct sockaddr_in));
    newUser->pixel = pixel;
    newUser->time = time;
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

void addDisconnectedUser(DisconnectedUser **disconnectedUserList, int pixel, time_t time, char * ip)
{
    DisconnectedUser *newDisconnectedUser = malloc(sizeof(DisconnectedUser));
    newDisconnectedUser->pixel = pixel;
    newDisconnectedUser->time = time;
    newDisconnectedUser->ip = ip;
    printf("addDisconnectedUser : %s \n", newDisconnectedUser->ip);
    newDisconnectedUser->suivant = NULL;
    newDisconnectedUser->precedent = NULL;
    if (*disconnectedUserList == NULL)
    {
        *disconnectedUserList = newDisconnectedUser;
    }
    else
    {
        DisconnectedUser *tmp = *disconnectedUserList;
        while (tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = newDisconnectedUser;
        newDisconnectedUser->precedent = tmp;
    }
}

void deleteDisconnectedUser(DisconnectedUser **disconnectedUserList, DisconnectedUser *disconnectedUser)
{
    if (disconnectedUser->precedent == NULL)
    {
        *disconnectedUserList = disconnectedUser->suivant;
    }
    else
    {
        disconnectedUser->precedent->suivant = disconnectedUser->suivant;
    }
    if (disconnectedUser->suivant != NULL)
    {
        disconnectedUser->suivant->precedent = disconnectedUser->precedent;
    }
    free(disconnectedUser);
}

void deleteDisconnectedUserTimout(DisconnectedUser **disconnectedUserList)
{
    DisconnectedUser *tmp = *disconnectedUserList;
    time_t now = time(NULL);
    if (tmp == NULL)
    {
        return;
    }
    while (tmp != NULL)
    {
        if (difftime(now, tmp->time) > 60)
        {
            printf("deleteDisconnectedUserTimout : %s \n", tmp->ip);
            deleteDisconnectedUser(disconnectedUserList, tmp);
        }
        tmp = tmp->suivant;
    }
}

int userReco(struct sockaddr_in *sockin, int socket, DisconnectedUser **listDisconnectedUser, User **userList)
{
    printf("userReco\n");
    DisconnectedUser *tmp = *listDisconnectedUser;
    while (tmp != NULL)
    {
        if (strcmp(inet_ntoa(sockin->sin_addr), tmp->ip) == 0)
        {
            printf("userReco : user found\n");
            addUser(userList, socket, sockin, tmp->pixel, tmp->time);
            deleteDisconnectedUser(listDisconnectedUser, tmp);
            return 1;
        }
        tmp = tmp->suivant;
    }
    return 0;
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
    free(user->sockin);
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
        User *suivant = tmp->suivant;
        free(tmp->sockin);
        free(tmp);
        tmp = suivant;
    }
}

void freeDisconnectedUserList(DisconnectedUser *disconnectedUserList) 
{
    DisconnectedUser *tmp = disconnectedUserList;
    while (tmp != NULL)
    {
        DisconnectedUser *suivant = tmp->suivant;
        free(tmp->ip);
        free(tmp);
        tmp = suivant;
    }
}
