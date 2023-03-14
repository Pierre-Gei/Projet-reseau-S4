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
#include "matrices.h"

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

void setServer(int argc, char *argv[], int *PORT, Matrix *matrix)
{
    *PORT = IPPORT_USERRESERVED;
    matrix->width = 80;
    matrix->height = 40;
    matrix->pixel_min = 10;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0 && atoi(argv[i + 1]) > 0)
        {
                *PORT = atoi(argv[i + 1]);
        }

        if (strcmp(argv[i], "-s") == 0)
        {
            char *dimensions[20];
            char *token = strtok(argv[i + 1], "x");
            int size = 0;
            while (token != NULL)
            {
                dimensions[size++] = token;
                token = strtok(NULL, "x");
            }
            if (size == 2 && atoi(dimensions[0]) > 0 && atoi(dimensions[1]) > 0)
            {
                matrix->width = atoi(dimensions[0]);
                matrix->height = atoi(dimensions[1]);
            }
        }

        if (strcmp(argv[i], "-l") == 0 && atoi(argv[i + 1]) > 0)
        {
            matrix->pixel_min = atoi(argv[i + 1]);
        }
    }
    initPixelsMatrix(matrix);
    // printMatrix(*matrix);
}

// fonction qui lit une commande avec des parametres

void readCommand(char *messageRecu, char *messageEnvoi,Matrix *matrix)
{
    printf("messageRecu: %s\n", messageRecu);
    int len = strcspn(messageRecu, "\n");
    messageRecu[len] = '\0';

    int argc = 0;
    char *argv[100];
    char afficheM[matrix->height*matrix->width*4];
    char *dimension[20];
    int size_dim = 0;

    char *token = strtok(messageRecu, " ");
    while (token != NULL)
    {
        printf("token: %s\n", token);
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (strcmp(argv[0], "/getMatrix") == 0)
    {
        char Temp[6];
        for (int i = 0; i < matrix->height; i++)
        {
            for (int j = 0; j < matrix->width; j++)
            {
                strcat(afficheM,strcpy(Temp,matrix->pixels[i][j]));
            }
        }
        printf("%s",afficheM);
        strcpy(messageEnvoi, afficheM);
    }
    else if (strcmp(argv[0], "/getSize") == 0)
    {
        char s[10];
        sprintf(s,"%dx%d",matrix->width,matrix->height);
        strcpy(messageEnvoi, s);
    }
    else if (strcmp(argv[0], "/setPixel") == 0)
    {
        printf("setPixel\n");
        if (argc == 3)
        {
            while (argv[1] != NULL)
            {
                token = strtok(argv[1], "x");
                while (token != NULL)
                {
                    printf("token: %s\n", token);
                    dimension[size_dim++] = token;
                    token = strtok(NULL, "x");
                }
                argv[1] = NULL;
            }
            strcpy(matrix->pixels[atoi(dimension[0])][atoi(dimension[1])],argv[2]);
            strcpy(messageEnvoi, "00 OK\n");
        }
        else
        {
            strcpy(messageEnvoi, "10 Bad command\n");
        }
    }
    else if (strcmp(argv[0], "/getLimits") == 0)
    {
        printf("getLimits\n");
    }
    else if (strcmp(argv[0], "/getVersion") == 0)
    {
        printf("getVersion\n");
    }
    else
    {
        strcpy(messageEnvoi, "99 Unknown command\n");
    }
}
