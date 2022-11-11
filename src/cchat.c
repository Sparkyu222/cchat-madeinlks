#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#include "color.h"
#include "thrterm.h"
#include "var.h"
#include "cserver.h"
#include "cclient.h"

int main (int argc, char **argv) {
  int opt;

  if ( argc > 2 ) {
    puts(RED"Syntaxe incorrecte"RESET);
    puts("Utilisation :");
    puts("-s\t -- Active le mode serveur");
    puts("-c\t -- Active le mode client");
    puts("-h\t -- Affiche cette page d'aide");
    exit(EXIT_FAILURE);
  }
  else {
    while ((opt = getopt (argc, argv, ":sch")) != -1) {
      switch (opt) {
        case 's' :
          puts("Cchat "RED"v4"RESET" madeinlks");
          puts("Mode serveur activé");
          fserver();
          break;
        case 'c' :
          puts("Cchat "RED"v4"RESET" madeinlks");
          puts("Mode client activé");
          fclient();
          break;
        case 'h' :
          puts("Utilisation :");
          puts("-s\t -- Active le mode serveur");
          puts("-c\t -- Active le mode client");
          puts("-h\t -- Affiche cette page d'aide");
          exit(EXIT_SUCCESS);
          break;
        default :
          puts(RED"Syntaxe incorrecte"RESET);
          puts("Utilisation :");
          puts("-s\t -- Active le mode serveur");
          puts("-c\t -- Active le mode client");
          puts("-h\t -- Affiche cette page d'aide");
          exit(EXIT_FAILURE);
      }
    }
  }

  signal(SIGINT, term);
  puts("Cchat "RED"v4"RESET" madeinlks");

  while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du client
    if (killthr == true) {
      term();
    }
  }

return EXIT_SUCCESS;
}