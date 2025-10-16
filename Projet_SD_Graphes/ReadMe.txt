README – Projet Algorithme de DINIC – Flot Maximum
======================================================================================================================================================
------------------------------------------------------------------------------------------------------------------------------------------------------
Contenu

Ce projet implémente l'algorithme de DINIC en langage C pour calculer le flot maximal dans un graphe orienté.
Le graphe est fourni au format DIMACS, via un fichier texte contenant les sommets, les arcs et leurs capacités.

Le programme principal se trouve dans le fichier : `Projet.c`

Il utilise les fichiers d'en-tête suivants :
- `arc.h`
- `sommet.h`
- `graphe.h`
- `chemin.h`

------------------------------------------------------------------------------------------------------------------------------------------------------

Compilation

Pour compiler le programme, deux méthodes sont possibles : soit manuellement en ligne de commande avec gcc, soit automatiquement en utilisant le Makefile fourni.
Les deux aboutissent à la création de l’exécutable Projet prêt à être lancé.
---------------------------------------------------------------------------------
Méthode 1 – Compilation manuelle (via terminal)

1. Ouvrir un terminal dans le dossier contenant les fichiers `.c` et `.h`
2. Entrer la commande suivante :

gcc -o Projet Projet.c

Cela génère un exécutable nommé `Projet`.
---------------------------------------------------------------------------------
Méthode 2 – Compilation automatique avec Makefile

Un fichier `Makefile` est présent dans le dossier. Pour compiler automatiquement :

1. Ouvrir un terminal dans le dossier contenant les fichiers `.c` et `.h`
2. Entrer la commande suivante :

make

Cela crée également un exécutable `Projet`.
En cas de besoin de nettoyage complet (et puis une recompilation) :

make clean
make

------------------------------------------------------------------------------------------------------------------------------------------------------
Exécution

Le programme lit un fichier DIMACS (ou `.txt`) via l’entrée standard, applique l’algorithme de DINIC, et écrit le résultat dans un fichier de sortie.

La syntaxe d’exécution est la suivante :

./Projet nomFichierResultat.txt < nomFichierTest.max

- `nomFichierTest.max` : fichier DIMACS contenant la description du graphe.
- `nomFichierResultat.txt` : nom du fichier dans lequel seront écrits le flot maximal et les flots par arc.

Exemples :

./Projet resultats_net1.txt < net1.txt
./Projet resultats_G_100_300.txt < G_100_300.max


Le fichier de résultats contiendra :

- Le flot maximal calculé.
- Les flots par arc (uniquement ceux avec flot > 0).

------------------------------------------------------------------------------------------------------------------------------------------------------
Notes:

- L’exécution suppose que les fichiers de test sont bien formatés (conformes au format DIMACS).
- Le programme supporte des graphes de très grande taille (> 1000 sommets).

------------------------------------------------------------------------------------------------------------------------------------------------------

Projet réalisé par Nabil HANI et Matteo BOUVIER
Étudiants en IS3 – Polytech Lille
Année universitaire 2024/2025

-------------------------------------------------------------------------------------------------------------------------------------------------------
