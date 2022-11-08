# Cchat v1 - simple chat coded in c

Cchat est un client/serveur de tchat programmé en c, c'est un programme simple et très probablement mal optimisé.

Cette deuxième version apporte le chiffrage au messages, il déplace de trois caractères dans le code ASCII chaques caractère du message envoyé et les re-déplacent de 3 à la réception de celui-ci sur le client.

---

Avant de compiler :
Dans la ligne 36 du fichier `src/client_chatV1.c`, changez l'adresse IP contenue dans les doubles côtes en l'adresse IP du serveur.

Compilation (dans la racine du projet):
```
cmake .
make
```

Les executables se trouveront dans le fichier `build/`