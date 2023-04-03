/*Convertir des couleurs r, g, b en BASE64*/
void convert_RGB_BASE_64(int r, int g, int b, char *base64);
/*Convertir des couleurs BASE64 en r, g, b*/
void convert_BASE_64_RGB(char *base64, int *r, int *g, int *b);
/*Vérifier si une chaîne de caractères est bien en BASE64*/
int verif_BASE_64(char *base64);
/*Remplacer un pixel de la matrice par le nouveau en BASE64*/
void editPixel(Matrix m, int x, int y, char *base64);
/*Afficher la matrice dans le terminal*/
void printMatrix(Matrix m);
