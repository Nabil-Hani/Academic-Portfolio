#if ! defined (CHEMIN_H)
#define CHEMIN_H 1

/***********************************************************************************/
/*   IMPLANTATION                                                                  */
/*                                                                                 */
/*   Représentation d’un chemin dans un graphe par un tableau dynamique de sommets */
/*                                                                                 */
/* - Le champ taille est un entier représentant le nombre de sommets du chemin     */
/* - Le champ sommets pointe vers un tableau dynamique d'entier étant les          */
/*   identifiants des sommets du chemin                                            */
/***********************************************************************************/

struct chemin{
	int *sommets;
	int taille;
};

#endif
