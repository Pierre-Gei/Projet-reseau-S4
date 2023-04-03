/*Ajouter un utilisateur dans la liste des utilisateurs connectés*/
void addUser(User **userList, int socketClient, struct sockaddr_in *sockin, int pixel, time_t time);
/*Ajouter un utilisateur dans la liste des utilisateurs déconnectés*/
void addDisconnectedUser(DisconnectedUser **disconnectedUserList, int pixel, time_t time, char * ip);
/*Supprimer un utilisateur de la liste déconnecté lorsque son temps pour poser un pixel a été réinitialisé*/
void deleteDisconnectedUserTimout(DisconnectedUser **disconnectedUserList);
/*Supprimer un utilisateur de la liste déconnecté*/
void deleteDisconnectedUser(DisconnectedUser **disconnectedUserList, DisconnectedUser *disconnectedUser);
/*Trouver un utilisateur dans la liste des utilisateurs déconnectés pour le remettre dans la liste des utilisateurs connectés*/
int userReco(struct sockaddr_in *sockin, int socket, DisconnectedUser **listDisconnectedUser, User **userList);
/*Supprimer un utilisateur de la liste des utilisateurs connectés*/
void deleteUser(User **userList, User *user);
/*Trouver un utilisateur dans la liste des utilisateurs connectés grâce à sa socket*/
User *findUserBySocket(User *userList, int socket);
/*Libérer la mémoire de la liste des utilisateurs connectés*/
void freeUserList(User *userList);
/*Libérer la mémoire de la liste des utilisateurs déconnectés*/
void freeDisconnectedUserList(DisconnectedUser *disconnectedUserList);