# Cchat v1 - simple chat coded in c

Cchat est un simple client/serveur de tchat programmé en c, c'est un programme simple et très probablement mal optimisé.

Cette première version permet d'établir une connexion entre deux ordinateurs et qu'ils puissent s'envoyer des mesages entre eux en temps réel.

---

Avant de compiler :
Dans la ligne 36 du fichier `src/client_chatV1.c`, changez l'adresse IP contenue dans les doubles côtes en l'adresse IP du serveur.

Compilation (dans la racine du projet):
```
cmake .
make
```

Les executables se trouveront dans le fichier `build/`