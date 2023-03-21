void convert_RGB_BASE_64(int r, int g, int b, char *base64);
void convert_BASE_64_RGB(char *base64, int *r, int *g, int *b);
int verif_BASE_64(char *base64);
void editPixel(Matrix m, int x, int y, char *base64);
void printMatrix(Matrix m);
