#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <SDL2/SDL.h>
#include "structure.h"
#include "liaison.h"
#include "conversion.h"
#include "affichage.h"
#define LG_Message 256

int main(int argc, char *argv[])
{
    // Découpage des arguments
    if (argc < 4)
    {
        printf("Invalid arguments \n");
        exit(-1);
    }
    int PORT = 0;
    char *ip;
    for (int i = 0; i < argc; i++)
    {
        // Vérification de l'ip
        if (strcmp(argv[i], "-s") == 0)
        {
            ip = argv[i + 1];
        }
        // Vérification du port
        if (strcmp(argv[i], "-p") == 0 && atoi(argv[i + 1]) > 0)
        {
            PORT = atoi(argv[i + 1]);
        }
    }

    int socketClient;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[LG_Message];
    int ecrits = 0, lus = 0;

    char tmp[20];
    char timeText[20];
    int widthMatrix = 0, heightMatrix = 0;
    int colorPickerWidth = 0, colorPickerHeight = 0;
    int SIZE = 0;
    int limit = 0;
    int version = 0;
    int waitTime = 0;
    int getMatrixCpt = 0;
    int getWaitTimeCpt = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *tVersion = NULL;
    SDL_Rect rVersion;
    SDL_Texture *tLimits = NULL;
    SDL_Rect rLimits;
    SDL_Texture *tTime = NULL;
    SDL_Rect rTime;
    SDL_Color colorWhite = {255, 255, 255, 255};
    CASE cases[14];
    initColorPicker(cases);
    SDL_Point mouse;

    char color[5];
    strcpy(color, "////");

    int chrono = SDL_GetTicks();
    int chronoTime = SDL_GetTicks();

    // Création de la socket, protocole TCP
    socketClient = socket(PF_INET, SOCK_STREAM, 0);

    // Test de la création de la socket
    if (socketClient < 0)
    {
        perror("socket");
        exit(-1);
    }

    printf("Socket client créée avec succès ! (%d)\n", socketClient);

    // Préparation de l'adresse de la socket destination
    memset(&pointDeRencontreDistant, 0x00, sizeof(pointDeRencontreDistant));
    pointDeRencontreDistant.sin_family = PF_INET;
    inet_aton(ip, &pointDeRencontreDistant.sin_addr);
    pointDeRencontreDistant.sin_port = htons(PORT);

    // Demande de connexion
    if (connect(socketClient, (struct sockaddr *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant)) < 0)
    {
        perror("connect");
        exit(-2);
    }

    // Récupérer la taille de la matrice
    send_message(socketClient, "/getSize", ecrits);
    receive_message(socketClient, tmp, lus, 20);
    sscanf(tmp, "%dx%d", &widthMatrix, &heightMatrix);
    SIZE = (widthMatrix * heightMatrix * 4) * sizeof(char);
    printf("widthMatrix: %d, heightMatrix: %d \n", widthMatrix, heightMatrix);
    char messageRecu[SIZE];
    memset(tmp, 0, 20);

    init(&window, &renderer);
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Récupérer la version du serveur
    send_message(socketClient, "/getVersion", ecrits);
    receive_message(socketClient, tmp, lus, 20);
    sscanf(tmp, "%d", &version);
    char versionText[20];
    sprintf(versionText, "Version: %d", version);
    affichage_text(&tVersion, 20, &rVersion, &renderer, versionText, colorWhite);
    memset(tmp, 0, 20);
    rVersion.x = 10;
    rVersion.y = windowHeight - rVersion.h - 10;

    // Récupérer la limite de pixel par minute
    send_message(socketClient, "/getLimits", ecrits);
    receive_message(socketClient, tmp, lus, 20);
    sscanf(tmp, "%d", &limit);
    char limitText[20];
    sprintf(limitText, "Limit: %d p / min", limit);
    affichage_text(&tLimits, 20, &rLimits, &renderer, limitText, colorWhite);
    rLimits.x = 10;
    rLimits.y = windowHeight - rLimits.h - 10 - rVersion.h - 10;

    printf("Connexion au serveur réussie avec succès !\n\n");

    // Récupérer la matrice
    CASE colorRect[heightMatrix][widthMatrix];
    //Initialiser le color picker
    color_picker(windowWidth, windowHeight, cases, 14, &colorPickerWidth, &colorPickerHeight);
    send_message(socketClient, "/getMatrix", ecrits);
    // Récupérer la matrice
    do
    {
        char tmp2[SIZE];
        lus += receive_message(socketClient, tmp2, 0, SIZE);
        strcat(messageRecu, tmp2);
        if (lus == SIZE)
        {
            messageRecu[SIZE] = '\0';
        }

    } while (lus != SIZE);
    lus = 0;
    if (strlen(messageRecu) != 0)
    {
        //Convertir la chaine en tableau de case
        separate_string(messageRecu, SIZE, widthMatrix, heightMatrix, colorRect);
        //Positionner les cases
        position_case_matrix(windowWidth, windowHeight - colorPickerHeight - 20, widthMatrix, heightMatrix, colorRect);
    }
    else
    {
        exit(-1);
    }
    // Communication avec le serveur
    while (1)
    {
        SDL_Event event;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        // Envoie de message /getMatrix toutes les 200ms
        if (SDL_GetTicks() - chrono > 200)
        {
            chrono = SDL_GetTicks();
            sprintf(messageEnvoi, "/getMatrix");
            getMatrixCpt = 1;
        }

        // Envoie de message /getWaitTime toutes les 1000ms
        if (SDL_GetTicks() - chronoTime > 1000)
        {
            sprintf(messageEnvoi, "/getWaitTime");
            getMatrixCpt = 0;
            getWaitTimeCpt = 1;
            chronoTime = SDL_GetTicks();
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    exit(0);
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    for (int i = 0; i < 14; i++)
                    {
                        //Vérifier si la souris est dans un des carrés du color picker
                        if (SDL_PointInRect(&mouse, &cases[i].rect))
                        {
                            convert_RGB_BASE_64(cases[i].color.r, cases[i].color.g, cases[i].color.b, color);
                        }
                    }

                    for (int i = 0; i < heightMatrix; i++)
                    {
                        for (int j = 0; j < widthMatrix; j++)
                        {
                            //Vérifier si la souris est dans un des carrés de la matrice
                            if (SDL_PointInRect(&mouse, &colorRect[i][j].rect))
                            {
                                sprintf(messageEnvoi, "/setPixel %dx%d %s", j, i, color);
                                getMatrixCpt = 0;
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
        }

        if (strlen(messageEnvoi) != 0)
        {
            // Envoi du message au serveur
            send_message(socketClient, messageEnvoi, ecrits);
            memset(messageEnvoi, 0x00, LG_Message);
            memset(messageRecu, 0x00, SIZE);

            if (getMatrixCpt == 1)
            {
                do
                {
                    char tmp2[SIZE];
                    // Réception de la réponse du serveur en plusieurs fois s'il y a trop de données
                    lus += receive_message(socketClient, tmp2, 0, SIZE);
                    strcat(messageRecu, tmp2);
                    if (lus == SIZE)
                    {
                        messageRecu[SIZE] = '\0';
                    }

                } while (lus != SIZE);
                lus = 0;
                separate_string(messageRecu, SIZE, widthMatrix, heightMatrix, colorRect);
                position_case_matrix(windowWidth, windowHeight - colorPickerHeight - 20, widthMatrix, heightMatrix, colorRect);
                getMatrixCpt = 0;
            }
            else
            {
                // Réception de la réponse du serveur
                receive_message(socketClient, messageRecu, lus, SIZE);
            }
            if (getWaitTimeCpt == 1)
            {
                // Afficher le temps d'attente
                sscanf(messageRecu, "%d", &waitTime);
                sprintf(timeText, "Wait: %d s", waitTime);
                affichage_text(&tTime, 20, &rTime, &renderer, timeText, colorWhite);
                rTime.x = windowWidth - rTime.w - 10;
                rTime.y = windowHeight - rTime.h - 10;
                getWaitTimeCpt = 0;
            }
        }
        SDL_RenderClear(renderer);
        //Affichage de tous les éléments
        drawColorPicker(renderer, cases, 14);
        draw_matrix(renderer, widthMatrix, heightMatrix, colorRect);
        SDL_RenderCopy(renderer, tVersion, NULL, &rVersion);
        SDL_RenderCopy(renderer, tLimits, NULL, &rLimits);
        SDL_RenderCopy(renderer, tTime, NULL, &rTime);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    // Fermeture de la socket client
    close(socketClient);
    //Libération de la mémoire
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
