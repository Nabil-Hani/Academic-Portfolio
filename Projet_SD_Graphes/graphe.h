#if ! defined (GRAPHE_H)
#define GRAPHE_H 1

#include "sommet.h"

/********************************************************************************************************/
/*   IMPLANTATION                                                                                       */
/*                                                                                                      */
/*   Cette structure représente un graphe orienté.                                                      */
/*                                                                                                      */
/* - Le champ nb_sommets contient le nombre total de sommets dans le graphe.                            */
/* - Le champ sommets est un pointeur vers un tableau dynamique de structures Sommet.                   */
/* - Chaque sommet contient un pointeur vers sa liste d’arcs sortants.                                  */
/********************************************************************************************************/


struct Graphe {
    int nb_sommets;
    struct Sommet* sommets;
};


#endif
