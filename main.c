#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>

#define PORT IPPORT_USERRESERVED // = 5000
#define LG_Message 256

typedef struct User
{
    int socketClient;
    struct sockaddr_in *sockin;
    struct User *suivant;
    struct User *precedent;
} User;

void addUser(User **userList, int socketClient, struct sockaddr_in *sockin)
{
    User *newUser = malloc(sizeof(User));
    newUser->socketClient = socketClient;
    newUser->sockin = sockin;
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

struct pollfd *reallocPoll(struct pollfd *tabPoll, User *userList, int socketEcoute, int * size)
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
    for (int i = 0; i < sizeTab ; i++)
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

int main()
{
    User *userList = NULL;
    int socketEcoute;
    struct sockaddr_in pointDeRencontreLocal;
    struct pollfd *tab = malloc(sizeof(struct pollfd));
    socklen_t longueurAdresse;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[LG_Message];
    char messageRecu[LG_Message];
    int sizeTab = 1;
    int ecrits, lus;

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
            if (tab[i].revents !=0 && i == 0)
            {
                addUser(&userList, accept(socketEcoute, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse), &pointDeRencontreDistant);
                printf("Ajout d'un USER sur %s:%d\n\n", inet_ntoa(pointDeRencontreDistant.sin_addr), ntohs(pointDeRencontreDistant.sin_port));
            }
            if (tab[i].revents != 0 && i > 0)
            {
                memset(messageRecu, 0x00, LG_Message*sizeof(char));
                lus = read(tab[i].fd, messageRecu, LG_Message*sizeof(char));
                if (lus == 0)
                {
                    User *tmp = userList;
                    while (tmp->socketClient != tab[i].fd)
                    {
                        tmp = tmp->suivant;
                    }
                    printf("Suppression d'un USER sur %s:%d\n\n", inet_ntoa(tmp->sockin->sin_addr), ntohs(tmp->sockin->sin_port));
                    deleteUser(&userList, tmp);
                }
                else
                {
                    printf("Message reçu : %sde %s:%d\n\n", messageRecu, inet_ntoa(pointDeRencontreDistant.sin_addr), ntohs(pointDeRencontreDistant.sin_port));
                    User *tmp = userList;
                    while (tmp->socketClient != tab[i].fd)
                    {
                        tmp = tmp->suivant;
                    }
                    sprintf(messageEnvoi, "Ok\n");
                    ecrits = write(tmp->socketClient, messageEnvoi, strlen(messageEnvoi)*sizeof(char));

                    if (ecrits < 0)
                    {
                        perror("write");
                        exit(-4);
                    }
                    if (ecrits == 0)
                    {
                        User *tmp = userList;
                        while (tmp->socketClient != tab[i].fd)
                        {
                            tmp = tmp->suivant;
                        }
                        printf("Suppression d'un USER sur %s:%d\n\n", inet_ntoa(tmp->sockin->sin_addr), ntohs(tmp->sockin->sin_port));
                        deleteUser(&userList, tmp);
                    }
                }
            }

        }

    }
    // Fermeture de la socket d'écoute
    close(socketEcoute);
    free(tab);
    return 0;
}
