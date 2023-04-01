/*Envoyer un message au serveur*/
void send_message(int socketClient, char *messageEnvoi, int ecrits);
/*Recevoir un message du serveur*/
int receive_message(int socketClient, char *messageRecu, int lus, int LG_Message);