#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#include "color.h"
#include "thrterm.h"
#include "var.h"
#include "cserver.h"
#include "cclient.h"

int main (int argc, char **argv) {
  int opt, menu = true;

  if ( argc > 2 ) {                                                                                           // Teste les options reçu dans le main
    puts(RED"Syntaxe incorrecte"RESET);
    puts("Utilisation :");
    puts("-s\t -- Active le mode serveur");
    puts("-c\t -- Active le mode client");
    puts("-v\t -- Affiche la version actuelle de Cchat");
    puts("-h\t -- Affiche cette page d'aide");
    exit(EXIT_FAILURE);
  }
  else {
    while ((opt = getopt (argc, argv, ":schv")) != -1) {
      switch (opt) {
        case 's' :                                                                                            // -s : active le mode "serveur"
          menu = false;
          puts("Cchat madeinlks - Mode "YELLOW"serveur"RESET" ");
          fserver();
          break;
        case 'c' :                                                                                            // -c : active le mode "client"
          menu = false;
          puts("Cchat madeinlks - Mode "YELLOW"client"RESET);
          fclient();
          break;
        case 'h' :                                                                                            // -h : affiche l'aide
          puts("Utilisation :");
          puts("-s\t -- Active le mode serveur");
          puts("-c\t -- Active le mode client");
          puts("-v\t -- Affiche la version actuelle de Cchat");
          puts("-h\t -- Affiche cette page d'aide");
          exit(EXIT_SUCCESS);
          break;
        case 'v':                                                                                            // -v : affiche la version
          puts("Cchat madeinlks "RED"version 4"RESET"");
          exit(EXIT_SUCCESS);
          break;
        default :                                                                                            // Affiche l'aide quand l'utilisateur entre un argument non-existant
          puts(RED"Syntaxe incorrecte"RESET);
          puts("Utilisation :");
          puts("-s\t -- Active le mode serveur");
          puts("-c\t -- Active le mode client");
          puts("-v\t -- Affiche la version actuelle de Cchat");
          puts("-h\t -- Affiche cette page d'aide");
          exit(EXIT_FAILURE);
      }
    }
  }

  signal(SIGINT, term);                                                                                       // Attends et écoute le signal SIGINT (ctrl-c) et déclanche la fonction "term"

  if (menu == true) {                                                                                         // Affichage du menu si les arguments ne sont pas utilisés
    int choice, choicechk = true;
    puts("*--------------------------------*");
    puts("|             Cchat              |");
    puts("|           madeinlks            |");
    puts("*--------------------------------*");

    puts("Sélectionnez votre mode de tchat :");
    puts(GREEN"1 "RESET"- Mode serveur");
    puts(GREEN"2 "RESET"- Mode client");

    do {
      scanf("%d",&choice);

      switch (choice) {
        case 1 :
          choicechk = true;
          fserver();
          break;
        case 2 :
          choicechk = true;
          fclient();
          break;
        default :
        choicechk = false;
        puts(RED"Valeur incorrect, entrez une valeur correcte ("YELLOW"1"RED" ou "YELLOW"2"RED")"RESET);
      }
    } while (choicechk == false);

  }

  while (1) {                                                                                                 // Boucle qui attent l'arrivée du message de fermeture
    if (killthr == true) {
      term();
    }
  }

return EXIT_FAILURE;
}