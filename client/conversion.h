
void convert_BASE_64_RGB(char *base64, Uint8 *r, Uint8 *g, Uint8 *b);
void convert_RGB_BASE_64(int r, int g, int b, char *base64);
void separate_string(char string[], int size, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);