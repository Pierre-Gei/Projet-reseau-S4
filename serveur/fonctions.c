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
    // free(tabPoll);
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
        else if (strcmp(argv[i], "-s") == 0)
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
        else if (strcmp(argv[i], "-l") == 0 && atoi(argv[i + 1]) > 0)
        {
            matrix->pixel_min = atoi(argv[i + 1]);
        }
    }
    initPixelsMatrix(matrix);
}

void timeOut(User *userList, Matrix *matrix)
{
    User *tmp = userList;
    time_t now = time(NULL);
    if (tmp->pixel < matrix->pixel_min)
    {
        if (difftime(now, tmp->time) > 60)
        {
            tmp->pixel = matrix->pixel_min;
        }
    }
}

// fonction qui lit une commande avec des parametres

void readCommand(char *messageRecu, char *messageEnvoi, Matrix *matrix, User *user) ///// a tester
{
    printf("pixel : %d\n", user->pixel);
    int len = strcspn(messageRecu, "\n");
    messageRecu[len] = '\0';

    int argc = 0;
    char *argv[100];
    char afficheM[matrix->height * matrix->width * 4];
    char *dimension[20];
    int size_dim = 0;

    char *token = strtok(messageRecu, " ");
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (strcmp(argv[0], "/getMatrix") == 0)
    {
        int pos = 0;
        for (int i = 0; i < matrix->height; i++)
        {
            for (int j = 0; j < matrix->width; j++)
            {
                pos += sprintf(afficheM + pos, "%s", matrix->pixels[i][j]);
            }
        }
        strcpy(messageEnvoi, afficheM);
    }
    else if (strcmp(argv[0], "/getSize") == 0)
    {
        char s[10];
        sprintf(s, "%dx%d", matrix->width, matrix->height);
        strcpy(messageEnvoi, s);
    }
    else if (strcmp(argv[0], "/setPixel") == 0)
    {
        if (argc == 3)
        {
            while (argv[1] != NULL)
            {
                token = strtok(argv[1], "x");
                while (token != NULL)
                {
                    dimension[size_dim++] = token;
                    token = strtok(NULL, "x");
                }
                argv[1] = NULL;
            }
            if (atoi(dimension[0]) >= matrix->width || atoi(dimension[1]) >= matrix->height || atoi(dimension[0]) < 0 || atoi(dimension[1]) < 0)
            {
                strcpy(messageEnvoi, "11 Pixel out of bound\n");
                return;
            }

            if (verif_BASE_64(argv[2]) == 1)
            {
                strcpy(messageEnvoi, "12 Bad Color\n");
                return;
            }
            timeOut(user, matrix);
            if (user->pixel > 0)
            {
                if (user->pixel == matrix->pixel_min)
                {
                    user->time = time(NULL);
                }
                strcpy(matrix->pixels[atoi(dimension[1])][atoi(dimension[0])], argv[2]);
                user->pixel--;
                printf("pixel apres : %d\n", user->pixel);
                strcpy(messageEnvoi, "00 OK\n");
            }
            else
            {
                strcpy(messageEnvoi, "20 Out of quota\n");
            }
        }
        else
        {
            strcpy(messageEnvoi, "10 Bad command\n");
        }
    }
    else if (strcmp(argv[0], "/getLimits") == 0)
    {
        sprintf(messageEnvoi, "%d", matrix->pixel_min);
    }
    else if (strcmp(argv[0], "/getVersion") == 0)
    {
        strcpy(messageEnvoi, "1");
    }
    else if (strcmp(argv[0], "/getWaitTime") == 0)
    {
        timeOut(user, matrix);
        if (user->pixel > 0)
        {
            strcpy(messageEnvoi, "0\n");
        }
        else
        {
            sprintf(messageEnvoi, "%d\n", (int)(60 - difftime(time(NULL), user->time)));
        }
    }
    else
    {
        strcpy(messageEnvoi, "99 Unknown command\n");
    }
}
