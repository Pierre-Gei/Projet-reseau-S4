struct pollfd *reallocPoll(struct pollfd *tabPoll, User *userList, int socketEcoute, int * size);
void readCommand(char *messageRecu, char *messageEnvoi,Matrix *m, User *user);
void setServer(int argc, char *argv[], int *PORT, Matrix *matrix);