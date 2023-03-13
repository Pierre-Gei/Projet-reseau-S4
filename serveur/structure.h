typedef struct User
{
    int socketClient;
    struct sockaddr_in *sockin;
    struct User *suivant;
    struct User *precedent;
} User;

typedef struct Matrix
{
    int width;
    int height;
    int pixel_min;
    char **pixels;
}Matrix;

Matrix initMatrix(Matrix m);