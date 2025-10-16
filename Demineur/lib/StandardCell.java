package lib;

/************************************************************************************/
/* Classe représentant une cellule standard (ni bombe, ni spéciale).                */
/* Peut afficher un chiffre correspondant au nombre de bombes adjacentes,           */
/* ou rester vide si aucune bombe n’est à proximité.                                */
/************************************************************************************/

public class StandardCell extends AbstractCell {

    /************************************************************************************/
    /* Constructeur de cellule standard.                                                */
    /* Appelle le constructeur parent (AbstractCell) pour initialiser les attributs.    */
    /* Définit explicitement que cette cellule ne contient pas de bombe.                */
    /************************************************************************************/

    public StandardCell() {
        super();
        this.bombe = false;
    }

    /************************************************************************************/
    /* Affichage textuel de la cellule.                                                 */
    /*                                                                                  */
    /* retourne :                                                                       */
    /*  - "." si la cellule n’a pas encore été révélée                                  */
    /*  - " " (espace) si elle a été révélée et qu’aucune bombe n’est adjacente         */
    /*  - le nombre de bombes adjacentes (sous forme de chaîne) dans les autres cas     */
    /************************************************************************************/

    public String toString() {
        if (!this.devoilee) return ".";
        if (this.bombesAdjacentes == 0) return " ";
        return String.valueOf(this.bombesAdjacentes);
    }
}

