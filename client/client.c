#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
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
    if (argc < 4)
    {
        printf("Invalid arguments \n");
        exit(-1);
    }
    int PORT = 0;
    char *ip;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            ip = argv[i + 1];
        }
        if (strcmp(argv[i], "-p") == 0 && atoi(argv[i + 1]) > 0)
        {
            PORT = atoi(argv[i + 1]);
        }
    }

    int socketClient;
    struct sockaddr_in pointDeRencontreDistant;
    char messageEnvoi[LG_Message];
    int ecrits = 0 , lus = 0;
    char dimension[20];
    int widthMatrix = 0, heightMatrix = 0;
    int SIZE = 0;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    CASE cases[14];
    initTabCases(cases);
    SDL_Point mouse;
    char color[4];
    int chrono = SDL_GetTicks();

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

    send_message(socketClient, "/getSize", ecrits);

    

    receive_message(socketClient, dimension, lus, 20);

    
    sscanf(dimension, "%dx%d", &widthMatrix, &heightMatrix);
    SIZE = widthMatrix * heightMatrix * 4 + 1;
    printf("widthMatrix: %d, heightMatrix: %d \n", widthMatrix, heightMatrix);
    char messageRecu[SIZE];

    
    init(&window, &renderer);
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    printf("Connexion au serveur réussie avec succès !\n\n");

    CASE colorRect[heightMatrix][widthMatrix];

    send_message(socketClient, "/getMatrix", ecrits);
    receive_message(socketClient, messageRecu, lus, SIZE);
    if (strlen(messageRecu) != 0)
    {
        separate_string(messageRecu, SIZE, widthMatrix, heightMatrix, colorRect);
        position_case_matrix(width, 900, widthMatrix, heightMatrix, colorRect);
    }
    else 
    {
        exit(-1);
    }

    // Communication avec le serveur
    while (1)
    {
        
        memset(messageEnvoi, 0x00, LG_Message);
        SDL_Event event;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        //chronometre toutes les 200 millisecondes
        if (SDL_GetTicks() - chrono > 200)
        {
            chrono = SDL_GetTicks();
            send_message(socketClient, "/getMatrix", ecrits);
            receive_message(socketClient, messageRecu, lus, SIZE);
            if (strlen(messageRecu) != 0)
            {
                separate_string(messageRecu, SIZE, widthMatrix, heightMatrix, colorRect);
                position_case_matrix(width, 900, widthMatrix, heightMatrix, colorRect);
            }
            else 
            {
                exit(-1);
            }
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
                        if(SDL_PointInRect(&mouse, &cases[i].rect))
                        {
                            convert_RGB_BASE_64(cases[i].color.r, cases[i].color.g, cases[i].color.b, color);
                        }
                    }

                    for (int i = 0; i < heightMatrix; i++)
                    {
                        for (int j = 0; j < widthMatrix; j++)
                        {
                            if (SDL_PointInRect(&mouse, &colorRect[i][j].rect))
                            {
                                sprintf(messageEnvoi, "/setPixel %dx%d %s", j, i, color);
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

            memset(messageRecu, 0x00, SIZE);

            // Réception de la réponse du serveur
            receive_message(socketClient, messageRecu, lus, SIZE);
        }
        SDL_RenderClear(renderer);
        
        color_picker(renderer, width, height, messageRecu, cases, 14);
        draw_matrix(renderer, widthMatrix, heightMatrix, colorRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    // Fermeture de la socket client
    close(socketClient);

    return 0;
}
