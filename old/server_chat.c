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

char msgr[MSG_SIZE], msgw[MSG_SIZE], msgend[MSG_SIZE] = "EHV54OUm0nZWBpK", msgchk[16] = "Flr8YwZsGNYGe8z";  // Déclaration des différents types messages
int key;
int killthr = false;
int socketServer;
int socketClient;
pthread_t lt, wt;                                                                                   // ID des threads

void term ();                                                                                       // Déclaration de la fonction de terminisaion
void encode();                                                                                      // Déclaration de la fonction de chiffrement
void decode();                                                                                      // Déclaration de la fonction de déchiffrement
void encodechk();                                                                                   // Déclaration de la fonction de chiffrement du message test de synchronisation
void *listenT (void *vargp);                                                                        // Déclaration de la fontion de réception de messages
void *writeT (void *vargp);                                                                         // Déclaration de la fonction d'envoie de messges

int main () {
    int synchk=0;

    puts(YELLOW"Server "RESET"chat madeinlks --- version 3");

    puts ("");
    
    while ( key < 1 || key > 10 ) {                                                                 // Saisie de la clé
        puts("Saisissez votre clé de synchronisation (nombre entre 1 et 10)");
        printf(YELLOW);
        scanf("%d",&key);
        printf(RESET);
        
        if ( key < 1 || key > 10 ) {
            puts(RED"Valeur de clé incorrecte, le nombre doit être compris entre 1 et 10."RESET);
        }
    }

    puts("Attente d'une connexion...");

    signal(SIGINT, term);                                                                           // Écoute et attend le signal SIGINT pour exécuter la fonction "term"
      
    memset(&socketServer,0,sizeof(socketServer));                                                   // Mise à zéro du socket Server 
    memset(&socketClient,0,sizeof(socketClient));                                                   // Mise à zéro du socket Client

    socketServer = socket(AF_INET, SOCK_STREAM, 0);                                                 // Création du socket du serveur IPV4, TCP
    struct sockaddr_in addrServer;                                                                  // Structure de l'IP du serveur pour le socket
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);                                                 // Définition de de l'ip d'écoute: "htonl(INADDR_ANY)" pour ne pas définir d'ip spécifique au socket
    addrServer.sin_family = AF_INET;                                                                // IPV4
    addrServer.sin_port = htons(30000);                                                             // Définition du port                                          
    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));                   // Assignation du socket
    listen(socketServer, 1);                                                                        // Écoute sur le socket

    struct sockaddr_in addrClient;                                                                  // Structure pour le socket du client
    socklen_t csize = sizeof(addrClient);                                                           // Définition de la taille des paramètres pour le socket du client
    socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);                    // Attente de connexion auprès du client                                      
    printf(GREEN"Connexion avec le client effectuée.\n"RESET);

    encodechk();
    send(socketClient, msgchk, sizeof(msgchk), 0);

    recv(socketClient, &synchk, sizeof(synchk), 0);
    if (synchk == 1) {
        puts(RED"\t/!\\ Clé de synchronisation différente ! /!\\");
        puts(RED"Les messages reçus et envoyés seront incorrectement affichés !"RESET);
    }

    puts("");

    pthread_create(&lt, NULL, listenT, NULL);                                                       // Initialisation du thread d'envoi de messages
    pthread_create (&wt, NULL, writeT, NULL);                                                       // Initialisation du thread de reception de messages

    while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du client
      if (killthr == true) {
        term();
      }
    }


return EXIT_SUCCESS;
}

void *listenT (void *vargp) {                                                                       // Thread de réception de messages
    while (1) { 
        while ( killthr == false ) {
            recv(socketClient, msgr, sizeof(msgr), 0);                                              // Attente de la réception du message
            decode();

            if (strcmp(msgend,msgr) == 0 ){                                                         // Test si reception du message de fermeture
                killthr = true;
            }
            else {
                printf(YELLOW "%s" RESET "\n",msgr);                                                // Affichage du message reçu
            }
        }
    }
}

void *writeT (void *vargp) {                                                                        // Thread d'envoi de messages
    while(1) {
        printf(RESET);
        scanf(" %100[^\n]s",msgw);
        encode();                                                                                   // Chiffrement du message
        printf(RESET);
        send(socketClient, msgw, sizeof(msgw), 0);                                                  // Envoie du message sur le socket du client
    }
}

void decode() {                                                                                     // Fonction de déchiffrage de message
    int i;
    char msgtmp[MSG_SIZE];                                                                          // Variable de changement de caractère temporaire
    strcpy(msgtmp,msgr);                                                                            // Copiage du message reçu dans la variable temporaire
    for (i=0 ; i < MSG_SIZE ; i++ ) {                                                               // Déchifrage
        if (msgtmp[i] == '\0') {                                                                    // Si on atteint la fin de la chaîne, arrêter
            break;
        }
        else {
            msgtmp[i] = msgtmp[i] + key;
        }
    }
    strcpy(msgr,msgtmp);                                                                            // Remplacement du message chiffré par le message déchiffré
}

void encode() {                                                                                     // Fonction de chiffrage de message
    int i;
    char msgtmp[MSG_SIZE];                                                                          // Variable de changement de caractère temporaire
    
    if (killthr == false) {                                                                         // Test pour savoir si on envoie le message de fermeture, ici si faux, chiffre le message tapé
        strcpy(msgtmp,msgw);
        for (i=0 ; i < MSG_SIZE ; i++ ) {                                                           // Chiffrement
            if (msgtmp[i] == '\0') {                                                                // Si on atteint la fin de la chaîne, arrêter
                break;
            }
            else {
                msgtmp[i] = msgtmp[i] - key;
            }
        }
        strcpy(msgw,msgtmp);                                                                        // Remplacement du message non chiffré par le message chiffré
    }
    else {                                                                                          // Chiffrement du message de fermeture
        strcpy(msgtmp,msgend);
        for (i=0 ; i < MSG_SIZE ; i++ ) {
            if (msgtmp[i] == '\0') {
                break;
            }
            else {
                msgtmp[i] = msgtmp[i] - key;
            }
        }
        strcpy(msgend,msgtmp);                                                                      // Remplace le message de fermeture en clair par celui du chiffré
    }
}

void encodechk () {
    int i;
    char msgtmp[MSG_SIZE];                                                                          // Variable de changement de caractère temporaire
        strcpy(msgtmp,msgchk);
        for (i=0 ; i < MSG_SIZE ; i++ ) {                                                           // Chiffrement
            if (msgtmp[i] == '\0') {                                                                // Si on atteint la fin de la chaîne, arrêter
                break;
            }
            else {
                msgtmp[i] = msgtmp[i] - key;
            }
        }
        strcpy(msgchk,msgtmp); 
}

void term () {                                                                                      // Fonction de fermeture (CTRL+C et message)
    killthr = true;
    encode();                                                                                       // Chiffrage du message de fermeture
    send(socketClient, &msgend, sizeof(msgend), 0);                                                 // Envoie du message de fermeture
    pthread_cancel(lt);                                                                             // Kill tu thread de reçeption
    pthread_cancel(wt);                                                                             // Kill du thread d'envoi
    puts(RED"Fermeture..."RESET);                                                                   // Message de fermeture
    close(socketClient);                                                                            // Fermeture du socket client
    exit(EXIT_SUCCESS);
}