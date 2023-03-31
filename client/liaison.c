#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void send_message(int socketClient, char *messageEnvoi, int ecrits)
{
    // Envoi du message
    printf("SEND MESSAGE : %s\n",messageEnvoi);
    ecrits = write(socketClient, messageEnvoi, strlen(messageEnvoi) * sizeof(char));
    printf("ECRITS : %d\n",ecrits);
    if (ecrits < 0)
    {
        perror("write");
        exit(-1);
    }
}

int receive_message(int socketClient, char *messageRecu, int lus, int LG_Message)
{
    // Réception du message
    
    lus = read(socketClient, messageRecu, LG_Message);
    messageRecu[lus] = '\0';
    printf("LUS : %d\n",lus);
    printf("RECEIVE MESSAGE : %s\n",messageRecu);
    if (lus < 0)
    {
        perror("read");
        exit(-1);
    }
    else if (lus == 0)
    {
        exit(-1);
    }
    return lus;
}
