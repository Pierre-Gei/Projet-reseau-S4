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
#include "user.h"
#include "fonctions.h"

#define LG_Message 256

int main(int argc, char *argv[])
{
    Matrix matrix;
    matrix = initMatrix(matrix);
    int PORT = 0;
    setServer(argc, argv, &PORT, &matrix);
    printf("\nPort: %d\n", PORT);
    printf("Matrix: %d %d\n", matrix.width, matrix.height);
    printf("Pixel min: %d\n", matrix.pixel_min);
    User *userList = NULL;
    int socketEcoute;
    struct sockaddr_in pointDeRencontreLocal;
    struct pollfd *tab = malloc(sizeof(struct pollfd));
    socklen_t longueurAdresse;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[matrix.height * matrix.width * 4];
    char messageRecu[LG_Message];
    int sizeTab = 1;
    int ecrits, lus;
    int error;

    // Création de la socket, protocole TCP
    socketEcoute = socket(PF_INET, SOCK_STREAM, 0);

    // Test de la création de la socket
    if (socketEcoute < 0)
    {
        perror("socket");
        exit(-1);
    }

    printf("Socket créée avec succès ! (%d)\n", socketEcoute);

    // Préparation de l'adresse de la socket
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    pointDeRencontreLocal.sin_port = htons(PORT);

    // Association de la socket à l'adresse locale
    if (bind(socketEcoute, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse) < 0)
    {
        perror("bind");
        exit(-2);
    }

    printf("Socket associée avec succès !\n");

    // Taille file d'attente
    if (listen(socketEcoute, 5) < 0)
    {
        perror("listen");
        exit(-3);
    }

    printf("Socket placée en écoute passive ...\n");

    // Attente de la demande de connexion d'un client
    while (1)
    {
        tab = reallocPoll(tab, userList, socketEcoute, &sizeTab);
        poll(tab, sizeTab, 1000);
        for (int i = 0; i < sizeTab; i++)
        {
            User *tmp = findUserBySocket(userList, tab[i].fd);
            if (tab[i].revents != 0 && i == 0)
            {
                addUser(&userList, accept(socketEcoute, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse), &pointDeRencontreDistant, matrix.pixel_min);
                printf("Ajout d'un USER sur %s:%d\n\n", inet_ntoa(pointDeRencontreDistant.sin_addr), ntohs(pointDeRencontreDistant.sin_port));
            }
            if (tab[i].revents != 0 && i > 0)
            {

                memset(messageRecu, 0x00, LG_Message * sizeof(char));
                lus = read(tab[i].fd, messageRecu, LG_Message * sizeof(char));
                if (lus < 0)
                {
                    perror("read");
                    exit(-4);
                }
                else if (lus == 0)
                {
                    printf("Suppression d'un USER sur %s:%d\n\n", inet_ntoa(tmp->sockin->sin_addr), ntohs(tmp->sockin->sin_port));
                    deleteUser(&userList, tmp);
                }
                else
                {
                    if (strlen(messageRecu) > 0)
                    {
                        printf("Message de %s:%d : %s\n", inet_ntoa(tmp->sockin->sin_addr), ntohs(tmp->sockin->sin_port), messageRecu);
                        readCommand(messageRecu, messageEnvoi, &matrix, tmp);
                        // sprintf(messageEnvoi, "Ok\n");
                        ecrits = write(tmp->socketClient, messageEnvoi, strlen(messageEnvoi) * sizeof(char));

                        if (ecrits < 0)
                        {
                            perror("write");
                            exit(-4);
                        }
                        if (ecrits == 0)
                        {
                            printf("Suppression d'un USER sur %s:%d\n\n", inet_ntoa(tmp->sockin->sin_addr), ntohs(tmp->sockin->sin_port));
                            deleteUser(&userList, tmp);
                        }
                    }
                    else
                        continue;
                }
            }
        }
    }
    // Fermeture de la socket d'écoute
    close(socketEcoute);
    freeUserList(userList);
    return 0;
}
