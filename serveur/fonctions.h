struct pollfd *reallocPoll(struct pollfd *tabPoll, User *userList, int socketEcoute, int * size);
void readCommand(char *messageRecu);