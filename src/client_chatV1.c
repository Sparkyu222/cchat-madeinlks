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

int killthr = false;
int socketClient;
char msg[MSG_SIZE];
char msgend[MSG_SIZE] = "#-1exitquit";
pthread_t lt, wt;                                                                                   // ID des threads

void term ();
void *listenT (void *vargp);
void *writeT (void *vargp);

int main () {
    puts("Client chat madeinlks v1 ("YELLOW"sans chiffrement"RESET") !");
    puts("Connection au serveur en cours...");

    signal(SIGINT, term);

    memset(&socketClient,0,sizeof(socketClient));
    socketClient = socket(AF_INET, SOCK_STREAM, 0);                                                 // Création du socket IPV4, TCP, ?
    struct sockaddr_in addrClient;                                                                  // Structure de l'ip du serveur pour le socket
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");                                            // IP du serveur                                            [MODIFIER L'IP ICI]
    addrClient.sin_family = AF_INET;                                                                // IPV4
    addrClient.sin_port = htons(30000);                                                             // Port du serveur
    if (connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient)) == -1 ) {   // Connexion au socket du serveur
        puts(RED"Impossible de se connecter au socket distant."RESET);                              // "If" pour savoir si la connexion s'est effectué
        exit(EXIT_FAILURE);
    }  
    printf(GREEN"Connexion avec le serveur effectuée.\n"RESET);
    puts("");

    pthread_create(&lt, NULL, listenT, NULL);                                                       // Initialisation du thread d'envoi de messages
    pthread_create (&wt, NULL, writeT, NULL);                                                       // Initialisation du thread de reception de messages

    while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du serveur
      if (killthr == true) {
        term();
      }
    }

return EXIT_SUCCESS;
}

void term (){                                                                                       // Fonction de fermeture (CTRL+C et message)
    puts(RED"Fermeture..."RESET);
    pthread_cancel(lt);                                                                             // Kill tu thread de reçeption
    pthread_cancel(wt);                                                                             // Kill du thread d'envoi
    send(socketClient, &msgend, sizeof(msgend), 0);                                                 // Envoie du message de fermeture
    close(socketClient);                                                                            // Fermeture du socket client
    exit(EXIT_SUCCESS);
} 

void *listenT (void *vargp) {                                                                       // Thread de réception de messages
    while (1) {
        recv(socketClient, msg, sizeof(msg), 0);                                                    // Attente de la réception du message

        if (strcmp(msgend,msg) == 0 ){                                                              // Test si reception du message de fermeture
            killthr = true;
        }
        else {
            printf(YELLOW "%s" RESET "\n",msg);                                                     // Affichage du message reçu
        }
    }
}

void *writeT (void *vargp) {                                                                        // Thread d'envoi de messages
    while(1) {
      printf(RESET);
      scanf(" %100[^\n]s",msg);
      printf(RESET);
      send(socketClient, msg, sizeof(msg), 0);                                                      // Envoie du message sur le socket du client
    }
}
