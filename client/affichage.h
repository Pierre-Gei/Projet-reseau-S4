/*Initialiser la fenêtre et le rendu du jeu*/
int init(SDL_Window **window, SDL_Renderer **renderer);
/*Initialiser une case à 0*/
CASE initCase(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h);
/*Initialiser rle color picker avec 14 couleurs de base*/
void initColorPicker(CASE cp[]);
/*Positionner le color picker et gérer la taille des cases*/
void color_picker(int width_screen, int height_screen, CASE cases[], int size_cases, int *widthColorPicker, int *heightColorPicker);
/*Afficher le color picker*/
void drawColorPicker( SDL_Renderer *renderer, CASE cases[], int size_cases);
/*Différencier le plus petit nombre*/
int min (int a, int b);
/*Initialiser la taille et la position des cases de la matrice*/
void position_case_matrix(int width_screen, int height_screen, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);
/*Afficher la matrice sur la fenêtre*/
void draw_matrix(SDL_Renderer *renderer, int MatrixWidth, int MatrixHeight, CASE colorRect[MatrixHeight][MatrixWidth]);
/*Afficher un texte*/
void affichage_text(SDL_Texture **texture, int Taille_Police, SDL_Rect *position, SDL_Renderer **renderer, char *texte, SDL_Color couleur);

