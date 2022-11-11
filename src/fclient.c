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
#include <cclient.h>
#include <color.h>
#include <thrterm.h>
#include <var.h>

void fclient () {
    int chk1 = 0, chk = 0, chkno = 0, no, synchk=0;
    char SERVERIP[12], r;

    while (chk == 0) {                                                                              // Demande de saisie de l'IP du serveur
        if (chkno == 1) {chk1 = 0;}
        printf("Entrez l'adresse du serveur : \n"YELLOW);
        scanf("%11s",SERVERIP);
        printf(RESET);

        if (r != '\n') {
        while ((no = getchar()) != '\n');
        }

            while (chk1 == 0) {
                printf("Vous avez bien tapé l'adresse ? (Y/n) ");                                   // Confirmation de syntaxe
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

    while ( key < 1 || key > 10 ) {                                                                 // Saisie de la clé
        puts("Saisissez votre clé de synchronisation (nombre entre 1 et 10)");
        printf(YELLOW);
        scanf("%d",&key);
        printf(RESET);
        
        if ( key < 1 || key > 10 ) {
            puts(RED"Valeur de clé incorrect, le nombre doit être compris entre 1 et 10."RESET);
        }
    }

    puts("Tentative de connexion au serveur en cours...");

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

    recv(socketClient, msgchkr, sizeof(msgchkr), 0);
    decodechk();
    if (strcmp(msgchkr,msgchk) != 0) {
        synchk = 1;
        send(socketClient, &synchk, sizeof(synchk), 0);
        puts(RED"\t/!\\ Clé de synchronisation différente ! /!\\");
        puts(RED"Les messages reçus et envoyés seront incorrectement affichés !"RESET);
    }
    else {
        send(socketClient, &synchk, sizeof(synchk), 0);
    }

    puts("");

    pthread_create(&lt, NULL, listenT, NULL);                                                       // Initialisation du thread d'envoi de messages
    pthread_create (&wt, NULL, writeT, NULL);                                                       // Initialisation du thread de reception de messages

    while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du serveur
      if (killthr == true) {
        term();
      }
    }
}