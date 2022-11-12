#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>

#include "cserver.h"
#include "color.h"
#include "thrterm.h"
#include "var.h"

void fserver () {
    int synchk = 0, no;

    while ( key < 1 || key > 10 ) {                                                                         // Saisie de la clé
        puts("Saisissez votre clé de synchronisation (nombre entre 1 et 10)");
        printf(YELLOW);
        scanf("%d",&key);
        printf(RESET);
        
        if ( key < 1 || key > 10 ) {
            puts(RED"Valeur de clé incorrecte, le nombre doit être compris entre 1 et 10."RESET);
        }
    }

    if (key != '\n') {
        while ((no = getchar()) != '\n');
    }



    puts(CLEAR);
    puts("Attente d'une connexion...");

    memset(&socketServer,0,sizeof(socketServer));                                                           // Mise à zéro du socket Server 
    memset(&socketClient,0,sizeof(socketClient));                                                           // Mise à zéro du socket Client

    socketServer = socket(AF_INET, SOCK_STREAM, 0);                                                         // Création du socket du serveur IPV4, TCP
    struct sockaddr_in addrServer;                                                                          // Structure de l'IP du serveur pour le socket
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);                                                         // Définition de de l'ip d'écoute: "htonl(INADDR_ANY)" pour ne pas définir d'ip spécifique au socket
    addrServer.sin_family = AF_INET;                                                                        // IPV4
    addrServer.sin_port = htons(30000);                                                                     // Définition du port                                          
    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));                           // Assignation du socket
    listen(socketServer, 1);                                                                                // Écoute sur le socket

    struct sockaddr_in addrClient;                                                                          // Structure pour le socket du client
    socklen_t csize = sizeof(addrClient);                                                                   // Définition de la taille des paramètres pour le socket du client
    socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);                            // Attente de connexion auprès du client                                      
    printf(GREEN"Connexion avec le client effectuée.\n"RESET);

    encodechk();
    send(socketClient, msgchk, sizeof(msgchk), 0);

    recv(socketClient, &synchk, sizeof(synchk), 0);
    if (synchk == 1) {
        int chk2 = 0;
        char rs;
        puts(RED"\t/!\\ Clé de synchronisation différente ! /!\\");
        puts(RED"Les messages reçus et envoyés seront incorrectement affichés !"RESET);

        while (chk2 == 0) {
            printf(RED"Continuer ? "RESET"(y/N) ");
            scanf("%c",&rs);
                
            if (rs != '\n') {
                while ((no = getchar()) != '\n');
            }

            switch (rs) {
                case 'Y' :
                case 'y' :
                    chk2 = 1;
                    break;
                case '\n' :
                case 'N' :
                case 'n' :
                    exit(EXIT_SUCCESS);
                    break;
                default :
                    puts("Merci de rentrer une réponse valide ("YELLOW"y"RESET" ou "YELLOW"n"RESET")");
                    break;
            }
        }
    }

    puts("");

    pthread_create(&lt, NULL, listenT, NULL);                                                               // Initialisation du thread d'envoi de messages
    pthread_create (&wt, NULL, writeT, NULL);                                                               // Initialisation du thread de reception de messages
}