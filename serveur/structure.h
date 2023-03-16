typedef struct User
{
    int socketClient;
    struct sockaddr_in *sockin;
    int pixel;
    int temps;
    struct User *suivant;
    struct User *precedent;
} User;

typedef struct Matrix
{
    int width;
    int height;
    int pixel_min;
    char ***pixels;
}Matrix;

/*Initialiser la structure à 0*/
Matrix initMatrix(Matrix m);
/*Initialiser la matrice à la taille width et height*/
void initPixelsMatrix(Matrix *m);
/*Libérer la matrices*/
void freeMatrix(Matrix m);