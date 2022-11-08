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
#include "color.h"
#define MSG_SIZE 101

int killthr=false;
int socketServer;
int socketClient;
char msg[MSG_SIZE];
char msgend[MSG_SIZE] = "#-1exitquit";
pthread_t lt, wt;                                                                               // ID des threads

void term ();
void *listenT (void *vargp);
void *writeT (void *vargp);

int main () {
    puts("Serveur chat madeinlks v1 ("YELLOW"sans chiffrement !"RESET")");
    puts("Attente d'une connexion...");

    signal(SIGINT, term);                                                                       // Écoute et attend le signal SIGINT pour exécuter la fonction "term"
      
    memset(&socketServer,0,sizeof(socketServer));                                               // Mise à zéro du socket Server 
    memset(&socketClient,0,sizeof(socketClient));                                               // Mise à zéro du socket Client

    socketServer = socket(AF_INET, SOCK_STREAM, 0);                                             // Création du socket du serveur IPV4, TCP
    struct sockaddr_in addrServer;                                                              // Structure de l'IP du serveur pour le socket
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);                                             // Définition de de l'ip d'écoute: "htonl(INADDR_ANY)" pour ne pas définir d'ip spécifique au socket
    addrServer.sin_family = AF_INET;                                                            // IPV4
    addrServer.sin_port = htons(30000);                                                         // Définition du port                                          
    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));               // Assignation du socket
    listen(socketServer, 1);                                                                    // Écoute sur le socket

    struct sockaddr_in addrClient;                                                              // Structure pour le socket du client
    socklen_t csize = sizeof(addrClient);                                                       // Définition de la taille des paramètres pour le socket du client
    socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);                // Attente de connexion auprès du client                                      
    printf(GREEN"Connexion avec le client effectuée.\n"RESET);
    puts("");

    pthread_create(&lt, NULL, listenT, NULL);                                                   // Initialisation du thread d'envoi de messages
    pthread_create (&wt, NULL, writeT, NULL);                                                   // Initialisation du thread de reception de messages

    while (1) {                                                                                 // Boucle qui attent l'arrivée du message de fermeture de la part du client
      if (killthr == true) {
        term();
      }
    }


return EXIT_SUCCESS;
}

void term (){                                                                                   // Fonction de fermeture (CTRL+C et message)
    puts(RED"Fermeture..."RESET);
    pthread_cancel(lt);                                                                         // Kill tu thread de reçeption
    pthread_cancel(wt);                                                                         // Kill du thread d'envoi
    send(socketClient, &msgend, sizeof(msgend), 0);                                             // Envoie du message de fermeture
    close(socketClient);                                                                        // Fermeture du socket du serveur
    close(socketServer);                                                                        // Fermeture du socket du client
    exit(EXIT_SUCCESS);
} 

void *listenT (void *vargp) {                                                                   // Thread de réception de messages
    while (1) {
        recv(socketClient, msg, sizeof(msg), 0);                                                // Attente de la réception du message

        if (strcmp(msgend,msg) == 0 ){                                                          // Test si reception du message de fermeture
            killthr = true;
        }
        else {
            printf(YELLOW "%s" RESET "\n",msg);                                                 // Affichage du message reçu
        }
    }
}

void *writeT (void *vargp) {                                                                    // Thread d'envoi de messages
    while(1) {
      printf(RESET);
      scanf(" %100[^\n]s",msg);
      printf(RESET);
      send(socketClient, msg, sizeof(msg), 0);                                                  // Envoie du message sur le socket du client
    }
}
