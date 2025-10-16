package lib;

import java.util.*;
import exceptions.*;

/************************************************************************************/
/* Classe principale représentant la logique du jeu du Démineur.                    */
/* Gère la grille, les règles de révélation, la détection de victoire ou défaite,   */
/* et l'intégration avec l'interface graphique.                                     */
/************************************************************************************/

public class Demineur {

    private int lignes;                     // Nombre total de lignes dans la grille
    private int colonnes;                   // Nombre total de colonnes dans la grille
    private int nombreBombes;               // Nombre de bombes à placer dans la partie
    private AbstractCell[][] grille;        // Grille de cellules (chaque cellule peut être standard ou piégée)
    private boolean[][] visitee;            // Matrice indiquant les cellules déjà visitées (pour la propagation)
    private boolean premierClic;            // Indique si l'utilisateur est en train d'effectuer son tout premier clic
    private int nombreClics;                // Compteur total de clics effectués pendant la partie
    private int cellulesARendreVisibles;    // Nombre de cellules encore à révéler pour gagner

    /************************************************************************************/
    /* Constructeur principal du moteur de jeu.                                         */
    /* Initialise les attributs et prépare la grille vide avec des cellules standards.  */
    /*                                                                                  */
    /* Paramètres :                                                                     */
    /*  - lignes         : nombre de lignes dans la grille                              */
    /*  - colonnes       : nombre de colonnes dans la grille                            */
    /*  - nombreBombes   : nombre total de bombes à placer dans la partie               */
    /************************************************************************************/

    public Demineur(int lignes, int colonnes, int nombreBombes) {
        this.lignes = lignes;
        this.colonnes = colonnes;
        this.nombreBombes = nombreBombes;
        this.grille = new AbstractCell[lignes][colonnes];
        this.premierClic = true;
        this.nombreClics = 0;
        initialiserGrille(); // Remplit la grille avec des cellules standards
    }

    /************************************************************************************/
    /* Remplit la grille avec uniquement des cellules standards.                        */
    /* Initialise également le compteur de cellules à découvrir (hors bombes).          */
    /************************************************************************************/

    private void initialiserGrille() {
        for (int i = 0; i < this.lignes; i++)
            for (int j = 0; j < this.colonnes; j++)
                this.grille[i][j] = new StandardCell();
        this.cellulesARendreVisibles = this.lignes * this.colonnes - this.nombreBombes;    // On soustrait les bombes pour savoir combien de cellules doivent être révélées
    }

    //Méthodes d’accès utilisées par la GUI

    /* retourne le nombre de lignes dans la grille */
    public int getRowCount() {
        return this.lignes;
    }

    /* retourne nombre de colonnes dans la grille */
    public int getColCount() {
        return this.colonnes;
    }

    /* retourne le nombre total de bombes à placer */
    public int getBombCount() {
        return this.nombreBombes;
    }

    /* retourne le nombre de clics effectués depuis le début de la partie */
    public int getClickCount() {
        return this.nombreClics;
    }

    /************************************************************************************/
    /* Paramètres :                                                                     */
    /*  - ligne    : indice de la ligne souhaitée                                       */
    /*  - colonne  : indice de la colonne souhaitée                                     */
    /*                                                                                  */
    /* Retourne :                                                                       */
    /*  - La cellule correspondante de la grille à la position [ligne][colonne]         */
    /************************************************************************************/

    public AbstractCell getCell(int ligne, int colonne) {
        return this.grille[ligne][colonne];
    }

    //  Coeur fonctionnel du jeu : révélation d'une cellule 

    /************************************************************************************/
    /* Tente de révéler la cellule située en (ligne, colonne).                          */
    /* Déclenche la pose des bombes si c'est le premier clic.                           */
    /* Gère la propagation, la victoire ou la défaite.                                  */
    /*                                                                                  */
    /* Paramètres :                                                                     */
    /*  - ligne    : indice de la ligne cliquée                                         */
    /*  - colonne  : indice de la colonne cliquée                                       */
    /*                                                                                  */
    /* Lève :                                                                           */
    /*  - InvalidMoveException si la case est déjà révélée ou si la partie est finie    */
    /************************************************************************************/

    public void revealCell(int ligne, int colonne) throws InvalidMoveException {

        if (this.grille[ligne][colonne].isRevealed()) {                  // Si la cellule a déjà été révélée, ce clic est invalide
            throw new InvalidMoveException("Cette case est déjà révélée.");
        }
                            
        if (this.premierClic) {                                  // Si c'est le tout premier clic : on place les bombes après ce clic
            placerBombes(ligne, colonne);                        // Place les bombes (hors de cette cellule)
            calculerBombesAdjacentes();                          // Calcule les bombes autour de chaque cellule
            visitee = new boolean[this.lignes][this.colonnes];   // Initialisation de la matrice de propagation
            this.premierClic = false;                            // Le premier clic a été effectué
        }

        nombreClics++;                                           // On compte le clic (pour affichage en haut de l'interface)
                                                  
        if (grille[ligne][colonne].isBomb()) {
            throw new GameLostException();                       // Si la cellule cliquée est une bombe, la partie est perdue
        }

        propagationRecursive(ligne, colonne);                    // Sinon, on commence la propagation de révélation

        if (this.cellulesARendreVisibles == 0) {
            throw new GameWonException();                        // Si toutes les cellules non piégées ont été révélées, victoire
        }
    }

    /************************************************************************************/
    /* Révèle récursivement les cellules voisines si aucune bombe n'est adjacente.      */
    /* La propagation s'arrête dès qu'une cellule voisine contient une bombe autour.    */
    /*                                                                                  */
    /* Paramètres :                                                                     */
    /*  - i : indice de la ligne courante                                               */
    /*  - j : indice de la colonne courante                                             */
    /************************************************************************************/

    private void propagationRecursive(int i, int j) {

        if (!dansLimites(i, j) || visitee[i][j] || grille[i][j].isRevealed()) return;    // Conditions d'arrêt : hors grille, déjà visitée, ou déjà révélée

        this.visitee[i][j] = true;             // Marque la cellule comme visitée
        this.grille[i][j].reveal();            // Révèle visuellement la cellule
        this.cellulesARendreVisibles--;        // Une cellule de moins à révéler

        if (this.grille[i][j].getAdjacentBombs() == 0) {         // Si aucune bombe adjacente, on propage aux voisines
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if (!(di == 0 && dj == 0))   // On évite la cellule elle-même
                        propagationRecursive(i + di, j + dj);
        }
    }

    /************************************************************************************/
    /* Place les bombes de manière aléatoire dans la grille sans toucher à une case     */
    /* spécifique (celle cliquée en premier).                                           */
    /*                                                                                  */
    /* Paramètres :                                                                     */
    /*  - ligSauf : ligne de la cellule à ne pas piéger                                 */
    /*  - colSauf : colonne de la cellule à ne pas piéger                               */
    /************************************************************************************/

    private void placerBombes(int ligSauf, int colSauf) {
        List<int[]> positions = new ArrayList<>();
        for (int i = 0; i < this.lignes; i++)             // Génère toutes les coordonnées possibles sauf la case cliquée
            for (int j = 0; j < this.colonnes; j++)
                if (!(i == ligSauf && j == colSauf))
                    positions.add(new int[]{i, j});

        Collections.shuffle(positions);              // Mélange les positions aléatoirement

        for (int i = 0; i < this.nombreBombes; i++) {     // Place les bombes sur les premières coordonnées sélectionnées
            int[] pos = positions.get(i);
            this.grille[pos[0]][pos[1]] = new BombCell(); // Remplace la cellule standard par une bombe
        }
    }

    /************************************************************************************/
    /* Calcule et stocke, pour chaque cellule non piégée, le nombre de bombes           */
    /* présentes dans les cellules voisines.                                            */
    /* Cette information est utilisée lors de l’affichage après révélation.             */
    /************************************************************************************/

    private void calculerBombesAdjacentes() {
        for (int i = 0; i < this.lignes; i++) {
            for (int j = 0; j < this.colonnes; j++) {
                if (!this.grille[i][j].isBomb()) {
                    int nb = 0;
                    for (int di = -1; di <= 1; di++)        // Vérifie toutes les cases autour (8 directions)
                        for (int dj = -1; dj <= 1; dj++) {
                            int ni = i + di;
                            int nj = j + dj;

                            if (dansLimites(ni, nj) && this.grille[ni][nj].isBomb()) {
                                nb++; // Incrémente si une bombe est détectée autour
                            }
                        }
                    this.grille[i][j].setAdjacentBombs(nb);      // Enregistre le total des bombes adjacentes
                }
            }
        }
    }

    /************************************************************************************/
    /* Vérifie si une position (i, j) est valide, c’est-à-dire dans les limites         */
    /* de la grille de jeu.                                                             */
    /*                                                                                  */
    /* Paramètres :                                                                     */
    /*  - i : indice de ligne                                                           */
    /*  - j : indice de colonne                                                         */
    /* Retourne :                                                                       */
    /*  - true si la position (i, j) est dans les bornes valides de la grille           */
    /*  - false sinon                                                                   */
    /************************************************************************************/

    private boolean dansLimites(int i, int j) {
        return i >= 0 && j >= 0 && i < this.lignes && j < this.colonnes;
    }

    /************************************************************************************/
    /* Fournit une cellule aléatoire sûre à suggérer à l'utilisateur.                   */
    /* Une cellule est dite "sûre" si elle n’a pas été révélée et n’est pas une bombe.  */
    /*                                                                                  */
    /* Retourne :                                                                       */
    /*  - Un tableau {i, j} contenant les coordonnées d'une cellule sûre                */
    /*  - null s’il n’existe plus aucune cellule sûre non révélée                       */
    /************************************************************************************/

    public int[] attemptRandomReveal() {

        List<int[]> options = new ArrayList<>();                  // Liste des cellules sûres : non révélées et sans bombe
        for (int i = 0; i < this.lignes; i++) {                        // Parcours de toute la grille
            for (int j = 0; j < this.colonnes; j++) {
                if (!grille[i][j].isRevealed() && !this.grille[i][j].isBomb()) {
                    options.add(new int[]{i, j});                 // Ajoute la cellule si elle est encore cachée et sûre
                }
            }
        }
        if (options.isEmpty()) return null;                       // Si aucune cellule sûre n’est trouvée, retourne null
        return options.get(new Random().nextInt(options.size())); // Retourne une cellule sûre choisie aléatoirement
    }
}    
