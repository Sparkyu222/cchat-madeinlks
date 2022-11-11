# Cchat v3 - simple chat coded in c

Cchat est un client/serveur de tchat programmé en c, c'est un programme simple et très probablement mal optimisé.

Nouvelles fonctionnalités apportées dans cette version :
- Clé de synchronisation : Possibilité de choisir le nombre de lettre à déplacer (entre 1 à 10 lettres) pour le chiffrement
- Un message test sera envoyé pour voir si le client et le serveur dispose de la même clé de synchronisation
- Le client demande désormais d'indiquer l'adresse IP du serveur

---

Avant de compiler :
Dans la ligne 36 du fichier `src/client_chatV1.c`, changez l'adresse IP contenue dans les doubles côtes en l'adresse IP du serveur.

Compilation (dans la racine du projet):
```
cmake .
make
```

Les executables se trouveront dans le fichier `build/`