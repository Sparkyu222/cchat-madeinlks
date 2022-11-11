#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#include "color.h"
#include "thrterm.h"
#include "var.h"
#include "cserver.h"
#include "cclient.h"

int main () {
  int choice;
  signal(SIGINT, term);
  puts("Cchat "RED"v4"RESET" madeinlks");

  puts("Sélectionnez votre mode (1 = Serveur, 0 = Client):");
  scanf("%d",&choice);
  if (choice == 1) {
    fserver();
  }
  else {
    fclient();
  }

  while (1) {                                                                                     // Boucle qui attent l'arrivée du message de fermeture de la part du client
    if (killthr == true) {
      term();
    }
  }

return EXIT_SUCCESS;
}