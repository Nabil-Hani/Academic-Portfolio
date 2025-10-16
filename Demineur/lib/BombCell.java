package lib; 

/************************************************************************************/
/* Classe représentant une cellule spéciale contenant une bombe.                    */
/* Hérite de AbstractCell pour réutiliser les attributs et comportements communs.   */
/************************************************************************************/

public class BombCell extends AbstractCell {

    /************************************************************************************/
    /* Constructeur d’une cellule-bombe.                                                */
    /* Appelle le constructeur de la classe mère pour initialiser les attributs communs.*/
    /* Ensuite, configure cette cellule pour qu'elle contienne une bombe.               */
    /************************************************************************************/

    public BombCell() {
        super();                // Initialise les champs hérités de AbstractCell (devoilee = false, bombe = false, bombesAdjacentes = 0)
        this.bombe = true;      // Cette cellule doit OBLIGATOIREMENT contenir une bombe, on la force à true
    }

    /************************************************************************************/
    /* Représentation visuelle de la cellule.                                           */
    /* Si elle est révélée, on affiche un symbole "X" pour indiquer une bombe.          */
    /* Sinon, on affiche un point "." pour signaler une cellule encore cachée.          */
    /*                                                                                  */
    /* retourne une chaîne de caractère selon l’état de révélation                      */
    /************************************************************************************/
    
    public String toString() {
      return this.devoilee ? "X" : "."; // Affiche X si visible (bombe révélée), sinon un point (non révélée)
    }

}
