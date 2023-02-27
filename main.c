#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT IPPORT_USERRESERVED // = 5000
#define LG_Message 256

int main()
{
    int socketEcoute;
    struct sockaddr_in pointDeRencontreLocal;
    socklen_t longueurAdresse;
    int socketDialogue;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[LG_Message];
    char messageRecu[LG_Message];
    int ecrits, lus;
    int retour;

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
        memset(messageEnvoi, 0x00, LG_Message * sizeof(char));
        memset(messageRecu, 0x00, LG_Message * sizeof(char));
        printf("Attente d'ue demande de connexion ...\n");
        // appel bloquant
        socketDialogue = accept(socketEcoute, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse);
        if (socketDialogue < 0)
        {
            perror("accept");
            close(socketDialogue);
            close(socketEcoute);
            exit(-4);
        }
        // Reception du message
        lus = read(socketDialogue, messageRecu, LG_Message * sizeof(char));
        switch (lus)
        {
        case -1: /*Erreur*/
            perror("read");
            close(socketDialogue);
            exit(-5);
        case 0: /*Socket fermée*/
            fprintf(stderr, "Socket fermée par le client !\n\n");
            close(socketDialogue);
        default: /*Message reçu*/
            printf("Message reçu : %s (%d octets)\n", messageRecu, lus);
        }
        // Envoi du message
        sprintf(messageEnvoi, "ok\n");
        ecrits = write(socketDialogue, messageEnvoi, strlen(messageEnvoi));
        switch (ecrits)
        {
        case -1: /*Erreur*/
            perror("write");
            close(socketDialogue);
            exit(-6);
        case 0: /*Socket fermée*/
            fprintf(stderr, "Socket fermée par le client !\n\n");
            close(socketDialogue);
        default: /*Message envoyé*/
            printf("Message envoyé : %s (%d octets)\n", messageEnvoi, ecrits);
        }
        // Fermeture de la socket de dialogue
        close(socketDialogue);
    }
    // Fermeture de la socket d'écoute
    close(socketEcoute);
    return 0;
}
