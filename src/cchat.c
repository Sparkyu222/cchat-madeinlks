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
#include "thrterm.h"
#include "var.h"
#include "cserver.h"
#include "cclient.h"

int main () {
    signal(SIGINT, term);
    puts("Cchat "RED"v4"RESET" madeinlks");
    
    fserver();
    
    while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du client
      if (killthr == true) {
        term();
      }
    }

return EXIT_SUCCESS;
}