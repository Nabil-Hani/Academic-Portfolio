#if ! defined (SOMMET_H)
#define SOMMET_H 1

#include "arc.h"

/***********************************************************************************/
/*   IMPLANTATION                                                                  */
/*                                                                                 */
/*   Cette structure représente un sommet dans un graphe orienté.                  */
/*                                                                                 */
/* - Le champ debut est un pointeur vers le premier arc de la liste d’adjacence    */
/*   du sommet. Cette liste permet de parcourir tous les arcs sortants du sommet.  */
/***********************************************************************************/


struct Sommet {
    struct Arc* successeurs;
};


#endif
