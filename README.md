# Cchat v4 - simple chat coded in c

Cchat est un client/serveur de tchat programmé en C, c'est un programme simple et très probablement mal optimisé.

Nouvelles fonctionnalités apportées dans cette version :
- Réorganisation des fichiers du projet en utilisant plus profédement cmake
- Combinaison du client et du serveur en un seul et même exécutable
- Un menu s'affiche lors du lancement du programme
- On peut sinon utiliser l'argument "-s" pour le mode serveur ou "-c" pour mode le client


Utilisation :
- Lancer directement l'exécutable pour afficher le menu et choisir le mode souhaité.
- Ou vous pouvez utiliser des arguments :
```1
./cchat -s                  // Active le mode serveur
./cchat -c                  // Active le mode client
```

---

Compilation (dans la racine du projet):
```
cmake .
make
```

Les executables se trouveront dans le fichier `build/`