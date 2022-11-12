# Cchat v4 - simple chat coded in c

Cchat est un client/serveur de tchat programmé en c, c'est un programme simple et très probablement mal optimisé.

Nouvelles fonctionnalités apportées dans cette version :
- Réorganisation des fichiers du projet en utilisant plus profédement cmake
- Combinaison du client et du serveur en un seul et même exécutable
- Un menu s'affiche lors du lancement du programme
- On peut sinon utiler l'argument "-s" pour le mode serveur ou "-c" pour mode le client

---

Compilation (dans la racine du projet):
```
cmake .
make
```

Les executables se trouveront dans le fichier `build/`