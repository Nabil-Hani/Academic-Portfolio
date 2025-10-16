PROJET PROGRAMMATION PAR OBJET : LE DÉMINEUR
AUTEUR : Nabil Hani

Ce projet de PPO propose une version du jeu du Démineur sur Java, construite avec une approche orientée objet. 
Je me suis concentré exclusivement sur le coeur du jeu, qui se trouve dans le package `lib`. 
L’idée était de bien séparer la logique du jeu de son interface graphique, pour que le moteur reste flexible, facile à maintenir, et réutilisable dans différents contextes.

Côté structure, le code repose sur une hiérarchie simple mais efficace :
- `AbstractCell` définit les comportements de base que toute cellule doit avoir (révélée ou non, présence de bombe, nombre de bombes voisines).
- Deux classes en héritent : `StandardCell` pour les cases vides ou numérotées, et `BombCell` pour les bombes. 
Ce choix rend le code plus clair, plus facile à lire, et surtout plus simple à faire évoluer si on voulait ajouter d’autres types de cellules.

Toute la logique du jeu est gérée dans la classe `Demineur`. Elle s’occupe de tout : placer les bombes après le premier clic (pour garantir un départ sans danger), 
révéler les cellules, propager automatiquement quand il n’y a pas de bombes autour, et détecter si le joueur a gagné ou perdu. 
J’ai aussi ajouté une petite option bonus : une suggestion automatique de coup sûr, grâce à la méthode `attemptRandomReveal()`.

Pour gérer les différents cas du jeu, j’ai utilisé des exceptions personnalisées. 
Elles rendent le code plus propre et permettent une communication plus claire avec l’interface utilisateur, qu’elle soit graphique ou en ligne de commande.

Améliorations possibles :
Voici quelques idées pour aller plus loin :S
- Ajouter des drapeaux pour marquer les bombes
- Intégrer un chronomètre ou plusieurs niveaux de difficulté
- Enregistrer les meilleurs scores, ou ajouter des tests automatiques
- Repenser la gestion de la grille dans une classe dédiée

Toutes ces améliorations pourraient être ajoutées sans problème, car le code actuel a été conçu pour être facilement extensible.

Pour lancer le jeu, compilez d’abord tous les fichiers avec la commande suivante dans un terminal :

javac exceptions/*.java gui/*.java lib/*.java

Ensuite, exécutez l’interface graphique avec :

java gui.DemineurUI  ou  java gui/DemineurUI

Une fenêtre s’ouvrira et vous proposera de choisir le nombre de lignes, de colonnes et de bombes. Le programme vérifie automatiquement que le nombre de bombes est cohérent (inférieur au nombre total de cases). Une fois la partie lancée, cliquez sur une case pour commencer. Le premier clic est toujours sans risque. Le but est de révéler toutes les cellules sans tomber sur une bombe. Un bouton permet aussi d’obtenir une suggestion de coup sûr si vous êtes bloqué.


Structure du projet :

Voici l’arborescence des fichiers et dossiers du projet après compilation. Elle montre l’organisation du code source (en .java) et des classes compilées (en .class), regroupées par packages fonctionnels (exceptions, gui, lib) :


├── exceptions
│   ├── GameLostException.class
│   ├── GameLostException.java
│   ├── GameWonException.class
│   ├── GameWonException.java
│   ├── InvalidMoveException.class
│   └── InvalidMoveException.java
├── gui
│   ├── DemineurUI.class
│   ├── DemineurUI.java
│   ├── GamePanel.class
│   ├── GamePanel.java
│   ├── SetupDialog.class
│   ├── SetupDialog.java
│   ├── TopPanel.class
│   └── TopPanel.java
├── lib
│   ├── AbstractCell.class
│   ├── AbstractCell.java
│   ├── BombCell.class
│   ├── BombCell.java
│   ├── Demineur.class
│   ├── Demineur.java
│   ├── StandardCell.class
│   └── StandardCell.java
└── README.md