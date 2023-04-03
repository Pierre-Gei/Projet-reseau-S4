/*Convertir des couleurs BASE64 en r, g, b*/
void convert_BASE_64_RGB(char *base64, Uint8 *r, Uint8 *g, Uint8 *b);
/*Convertir des couleurs r, g, b en BASE64*/
void convert_RGB_BASE_64(int r, int g, int b, char *base64);
/*Séparer la chaine de caractères en tableau de chaine de caractères*/
void separate_string(char string[], int size, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);