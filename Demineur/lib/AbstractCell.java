package lib; 

/************************************************************************************/
/* Classe abstraite représentant une cellule générique de la grille.                */
/* Toutes les cellules spécifiques (bombe ou standard) hériteront de cette classe.  */
/* Elle contient les attributs et méthodes de base liés à l’état de la cellule.     */
/************************************************************************************/

public abstract class AbstractCell {

    protected boolean devoilee;        // Attribut indiquant si la cellule a été révélée (true) ou non (false)
    protected boolean bombe;           // Attribut indiquant si la cellule contient une bombe
    protected int bombesAdjacentes;    // Nombre de bombes dans les 8 cases voisines de cette cellule

    /************************************************************************************/
    /* Constructeur par défaut.                                                         */
    /* Initialise la cellule comme non révélée, sans bombe, et sans bombes adjacentes.  */
    /************************************************************************************/

    public AbstractCell() {
        this.devoilee = false;        // Par défaut, la cellule est masquée
        this.bombe = false;           // Par défaut, la cellule ne contient pas de bombe
        this.bombesAdjacentes = 0;    // Par défaut, elle n’a pas de bombe adjacente
    }

    /************************************************************************************/
    /* Méthode permettant de savoir si la cellule a été révélée.                        */
    /*                                                                                  */
    /* retourne true si la cellule est révélée, false sinon                             */
    /************************************************************************************/

    public boolean isRevealed() {
        return devoilee;
    }

    /************************************************************************************/
    /* Méthode permettant de savoir si cette cellule contient une bombe.                */
    /*                                                                                  */
    /* retourne : true si la cellule est une bombe, false sinon                         */
    /************************************************************************************/

    public boolean isBomb() {
        return this.bombe;
    }

    /************************************************************************************/
    /* Méthode retournant le nombre de bombes autour de cette cellule.                  */
    /*                                                                                  */
    /* retourne un entier entre 0 et 8 (représentant le nombre de bombes voisines)      */
    /************************************************************************************/

    public int getAdjacentBombs() {
        return this.bombesAdjacentes;
    }

    /************************************************************************************/
    /* Définit si la cellule est une bombe.                                             */
    /*                                                                                  */
    /* Paramètre :                                                                      */
    /*  - bombe : true si la cellule est une bombe, false sinon                         */
    /************************************************************************************/

    public void setBomb(boolean bombe) {
        this.bombe = bombe;
    }

    /************************************************************************************/
    /* Modifie le nombre de bombes adjacentes.                                          */
    /*                                                                                  */
    /* Paramètre :                                                                      */
    /*  - n : le nombre de bombes voisines à stocker                                    */
    /************************************************************************************/

    public void setAdjacentBombs(int n) {
        this.bombesAdjacentes = n;
    }

    /************************************************************************************/
    /* Marque la cellule comme révélée.  (clic effectué par l’utilisateur)              */
    /************************************************************************************/

    public void reveal() {
        this.devoilee = true;
    }

    /************************************************************************************/
    /* Méthode abstraite que chaque sous-classe devra implémenter                       */
    /* pour afficher sa propre représentation graphique                                 */
    /* retourne une chaîne représentant l’état visuel de la cellule                     */
    /************************************************************************************/

    public abstract String toString();
}
