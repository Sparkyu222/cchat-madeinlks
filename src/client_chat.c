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

int killthr = false;                                                                                // Valeur d'appel de fermeture
int socketClient;                                                                                   // Initialisation de la variable du socket client
char msgr[MSG_SIZE], msgw[MSG_SIZE], msgend[MSG_SIZE] = "#-1exitquit";                              // Déclaration des différents types messages
pthread_t lt, wt;                                                                                   // ID des threads

void term ();                                                                                       // Déclaration de la fonction de fermeture
void encode();                                                                                      // Déclaration de la fonction de chiffrement
void decode();                                                                                      // Déclaration de la fonction de déchiffrement
void *listenT (void *vargp);                                                                        // Déclaration de la fontion de réception de messages
void *writeT (void *vargp);                                                                         // Déclaration de la fonction d'envoie de messges

int main () {
    int chk1 = 0, chk = 0, chkno = 0, no;
    char SERVERIP[12], r;
    
    puts(YELLOW"Client "RESET"chat madeinlks --- version 3");
    puts("");

    while (chk == 0) {                                                                              // Demande de saisie de l'IP du serveur
        if (chkno == 1) {chk1 = 0;}
        printf("Entrez l'adresse du serveur : \n"YELLOW);
        scanf("%11s",SERVERIP);
        printf(RESET);

        if (r != '\n') {
        while ((no = getchar()) != '\n');
        }

            while (chk1 == 0) {
                printf("Vous avez bien tapé l'adresse ? (Y/n) ");                                           // Confirmation de syntaxe
                scanf("%c",&r);
                
                if (r != '\n') {
                while ((no = getchar()) != '\n');
                }
                
                    printf("\n");

                    switch (r) {
                        case '\n' :
                        case 'Y' :
                        case 'y' :
                        chk = 1;
                        chk1 = 1;
                        break;
                        case 'N' :
                        case 'n' :
                        chk1 = 1;
                        chkno = 1;
                        break;
                        default :
                            puts("Merci de rentrer une réponse valide (y ou n)");
                        break;
                    }
            }
        }


    puts("Connection au serveur en cours...");

    signal(SIGINT, term);

    memset(&socketClient,0,sizeof(socketClient));
    socketClient = socket(AF_INET, SOCK_STREAM, 0);                                                 // Création du socket IPV4, TCP, ?
    struct sockaddr_in addrClient;                                                                  // Structure de l'ip du serveur pour le socket
    addrClient.sin_addr.s_addr = inet_addr(SERVERIP);                                               // IP du serveur
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
            msgtmp[i] = msgtmp[i] + 3;
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
                msgtmp[i] = msgtmp[i] - 3;
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
                msgtmp[i] = msgtmp[i] - 3;
            }
        }
        strcpy(msgend,msgtmp);                                                                      // Remplace le message de fermeture en clair par celui du chiffré
    }
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