#if ! defined (ARC_H)
#define ARC_H 1

/***********************************************************************************/
/*   IMPLANTATION                                                                  */
/*                                                                                 */
/*   Cette structure représente une arête orientée dans un graphe, utilisée        */
/*   notamment dans les algorithmes de flot.                                       */
/*                                                                                 */
/* - Le champ destination contient l’identifiant du sommet d’arrivée de l’arc.     */
/* - Le champ capacite représente la capacité maximale de l’arc, c’est-à-dire la   */
/*   quantité maximale de flot que cet arc peut transporter.                       */
/* - Le champ flot indique le flot actuellement présent sur cet arc.               */
/* - Le champ inverse est un pointeur vers l’arc inverse, ce qui est utile pour    */
/*   construire le graphe résiduel dans les algorithmes de flot.                   */
/* - Le champ suivant est un pointeur vers l’arc suivant dans la liste d’adjacence */
/*   du sommet d’origine.                                                          */
/***********************************************************************************/


struct Arc {
    int dest;
    int capa;
    int flot;
    struct Arc* reverse;
    struct Arc* suivant;
};


#define NIL ((struct Arc *) 0)

#endif
