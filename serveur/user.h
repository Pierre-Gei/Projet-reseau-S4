void addUser(User **userList, int socketClient, struct sockaddr_in *sockin, int pixel);
void deleteUser(User **userList, User *user);
User *findUserBySocket(User *userList, int socket);
void freeUserList(User *userList);