void convert_BASE_64_RGB(char *base64, int *r, int *g, int *b);
void convert_RGB_BASE_64(int r, int g, int b, char *base64);
void separate_string(char string[], int size, int width, int height, SDL_ColorRect colorRect[height][width]);