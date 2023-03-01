typedef struct User
{
    int socketClient;
    struct sockaddr_in *sockin;
    struct User *suivant;
    struct User *precedent;
} User;
