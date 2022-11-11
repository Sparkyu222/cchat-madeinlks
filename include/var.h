#include <stdbool.h>
#include <pthread.h>

#define MSG_SIZE 101
char msgr[MSG_SIZE], msgw[MSG_SIZE], msgend[MSG_SIZE] = "EHV54OUm0nZWBpK", msgchkr[16], msgchk[16] = "Flr8YwZsGNYGe8z"; // Déclaration des différents types messages
int key = 0, killthr = false;                                                                                           // Déclaration des variables de terminaisons
int socketClient, socketServer;                                                                                         // Déclaration des Sockets
pthread_t lt, wt;                                                                                                       // Déclaration des ID des threads
