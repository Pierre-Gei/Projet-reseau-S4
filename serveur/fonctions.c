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

struct pollfd *reallocPoll(struct pollfd *tabPoll, User *userList, int socketEcoute, int *size)
{
    int sizeTab = 1;

    User *tmp = userList;
    while (tmp != NULL)
    {
        sizeTab++;
        tmp = tmp->suivant;
    }
    tmp = userList;

    struct pollfd *newTab = malloc(sizeof(struct pollfd) * sizeTab);
    for (int i = 0; i < sizeTab; i++)
    {
        if (i == 0)
        {
            newTab[i].fd = socketEcoute;
            newTab[i].events = POLLIN;
        }
        else
        {
            newTab[i].fd = tmp->socketClient;
            newTab[i].events = POLLIN;
            tmp = tmp->suivant;
        }
    }
    free(tabPoll);
    *size = sizeTab;
    return newTab;
}

// fonction qui lit une commande avec des parametres

void readCommand(char *messageRecu)
{
    printf("messageRecu: %s\n", messageRecu);
    int len = strcspn(messageRecu, "\n");
    messageRecu[len] = '\0';

    int argc = 0;
    char *argv[100];

    char *token = strtok(messageRecu, " ");
    while (token != NULL)
    {
        printf("token: %s\n", token);
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (strcmp(argv[0], "/getMatrix") == 0)
    {
        printf("getMatrix\n");
    }
    else if (strcmp(argv[0], "/getSize") == 0)
    {
        printf("getSize\n");
    }
}