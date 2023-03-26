int init(SDL_Window **window, SDL_Renderer **renderer);
CASE initCase(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h);
void initTabCases(CASE cases[]);
void color_picker(SDL_Renderer *renderer, int width_screen, int height_screen, char *MessageEnvoi, CASE cases[], int size_cases);
int min (int a, int b);
void position_case_matrix(int width_screen, int height_screen, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);
void draw_matrix(SDL_Renderer *renderer, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);
