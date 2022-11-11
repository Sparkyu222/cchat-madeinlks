#define MSG_SIZE 101

extern char msgr[MSG_SIZE], msgw[MSG_SIZE], msgend[MSG_SIZE], msgchkr[16], msgchk[16];      // Déclaration des différents types messages
extern int key, killthr;                                                                    // Déclaration des variables de terminaisons
extern int socketClient, socketServer;                                                      // Déclaration des Sockets
extern pthread_t lt, wt;                                                                    // Déclaration des ID des threads