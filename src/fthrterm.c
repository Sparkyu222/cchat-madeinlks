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
#include "var.h"
#include "thrterm.h"

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

void decode () {                                                                                     // Fonction de déchiffrage de message
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

void encode () {                                                                                     // Fonction de chiffrage de message
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

void decodechk () {                                                                                  // Fonction de déchiffrage de message
    int i;
    char msgtmp[MSG_SIZE];                                                                          // Variable de changement de caractère temporaire
    strcpy(msgtmp,msgchkr);                                                                         // Copiage du message reçu dans la variable temporaire
    for (i=0 ; i < MSG_SIZE ; i++ ) {                                                               // Déchifrage
        if (msgtmp[i] == '\0') {                                                                    // Si on atteint la fin de la chaîne, arrêter
            break;
        }
        else {
            msgtmp[i] = msgtmp[i] + key;
        }
    }
    strcpy(msgchkr,msgtmp);                                                                         // Remplacement du message chiffré par le message déchiffré
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