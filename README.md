# Cchat v4 - simple chat coded in c

Cchat est un client/serveur de tchat programmé en C, un programme tout simple pour échanger des messages entre deux ordinateurs.

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
