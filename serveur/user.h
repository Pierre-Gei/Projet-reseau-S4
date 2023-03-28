void addUser(User **userList, int socketClient, struct sockaddr_in *sockin, int pixel, time_t time);
void addDisconnectedUser(DisconnectedUser **disconnectedUserList, int pixel, time_t time, char * ip);
void deleteDisconnectedUserTimout(DisconnectedUser **disconnectedUserList);
void deleteDisconnectedUser(DisconnectedUser **disconnectedUserList, DisconnectedUser *disconnectedUser);
int userReco(struct sockaddr_in *sockin, int socket, DisconnectedUser *listDisconnectedUser, User **userList);
void deleteUser(User **userList, User *user);
User *findUserBySocket(User *userList, int socket);
void freeUserList(User *userList);