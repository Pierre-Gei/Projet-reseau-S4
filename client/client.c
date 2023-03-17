#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LG_Message 256

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Invalid arguments \n");
        exit(-1);
    }
    int PORT = 0;
    char *ip;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            ip = argv[i + 1];
        }
        if (strcmp(argv[i], "-p") == 0 && atoi(argv[i + 1]) > 0)
        {
            PORT = atoi(argv[i + 1]);
        }
    }

    int socketClient;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[LG_Message];
    int ecrits, lus;

    // Création de la socket, protocole TCP
    socketClient = socket(PF_INET, SOCK_STREAM, 0);

    // Test de la création de la socket
    if (socketClient < 0)
    {
        perror("socket");
        exit(-1);
    }

    printf("Socket client créée avec succès ! (%d)\n", socketClient);

    // Préparation de l'adresse de la socket destination
    memset(&pointDeRencontreDistant, 0x00, sizeof(pointDeRencontreDistant));
    pointDeRencontreDistant.sin_family = PF_INET;
    inet_aton(ip, &pointDeRencontreDistant.sin_addr);
    pointDeRencontreDistant.sin_port = htons(PORT);

    // Demande de connexion
    if (connect(socketClient, (struct sockaddr *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant)) < 0)
    {
        perror("connect");
        exit(-2);
    }

    sprintf(messageEnvoi, "/getSize");

    ecrits = write(socketClient, messageEnvoi, strlen(messageEnvoi) * sizeof(char));

    if (ecrits < 0)
    {
        perror("write");
        exit(-3);
    }
    char dim[20];
    lus = read(socketClient, dim, 20 * sizeof(char));

    if (lus < 0)
    {
        perror("read");
        exit(-4);
    }
    int largeur, hauteur;
    sscanf(dim, "%dx%d", &largeur, &hauteur);
    int SIZE = largeur * hauteur * 4 + 1;
    printf("Largeur: %d, Hauteur: %d \n", largeur, hauteur);
    char messageRecu[SIZE];

    printf("Connexion au serveur réussie avec succès !\n\n");

    // Communication avec le serveur
    while (1)
    {
        printf("Message à envoyer : ");
        fgets(messageEnvoi, LG_Message * sizeof(char), stdin);

        // Suppression du caractère de fin de ligne
        messageEnvoi[strlen(messageEnvoi) - 1] = '\0';

        // Envoi du message au serveur
        ecrits = write(socketClient, messageEnvoi, strlen(messageEnvoi) * sizeof(char));

        if (ecrits < 0)
        {
            perror("write");
            exit(-3);
        }
        if (strlen(messageEnvoi) == 0)
        {
            printf("Message vide \n");
        }
        else
        {
            // Réception de la réponse du serveur
            memset(messageRecu, 0x00, SIZE);
            lus = read(socketClient, messageRecu, SIZE);

            if (lus < 0)
            {
                perror("read");
                exit(-4);
            }
            else if (lus == 0)
            {
                printf("Le serveur a coupé la connexion.\n");
                break;
            }
            else
            {
                printf("Réponse du serveur : %s\n\n", messageRecu);
            }
        }
    }

    // Fermeture de la socket client
    close(socketClient);

    return 0;
}
