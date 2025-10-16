#include <stdio.h>
#include <stdlib.h>
#define A 19 //Taille du plateau

/************************************************************/
/* Declaration de la structure Jeu                          */
/* plateau[A][A]: Chaîne de caractères - Matrice à afficher */
/* scoreX: Entier - score du joueur avec les croix          */
/* scoreO: Entier - score du joueur avec les ronds          */
/* tour: Entier - permet d'alterner les tours des joueurs   */
/************************************************************/
typedef struct {
    char plateau[A][A];
    int scoreX;
    int scoreO;
    int tour;
} Jeu;

/*******************************************************************************************************************/
/* Init_jeu : Action d'initialisation de la structure jeu : plateau vide, les scores = 0 et le tour au pion rond O */
/* pente  : Jeu - Resultat                                                                                         */
/*******************************************************************************************************************/

void init_jeu (Jeu *pente)
{
    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < A; j++)
        {
            pente -> plateau[i][j] = '.';
        }
    }
    pente -> scoreX = 0;
    pente -> scoreO = 0;
    pente -> tour = -1;  //-1 pour O et 1 pour X
}


/****************************************************************************************/
/* Affichage_plateau : Action d'affichage des element du jeu : le plateau et les scores */
/* pente : Jeu - Jeu a afficher - Donnee                                                */
/****************************************************************************************/
void affichage_plateau(Jeu pente)
{
    printf(" ");
    for(int col = 1; col <= A; col++)
    {
        printf("    %2d    ", col);
    }
    printf("\n");

    for (int i = 0; i < A; i++)
    {
        printf("%2d    ", i+1);
        for (int j = 0; j < A; j++)
        {
            printf("%c         ", pente.plateau[i][j]);
        }
        printf("\n");
    }
    printf("Nombre de pions capturés:\n");
    printf("X: %d           O: %d\n", pente.scoreX, pente.scoreO);
}

/********************************************************************************************************************************************/
/* verif_captures : Action pour verifier les captures dans toutes les directions, suppression des pions capturés et modification des scores */
/* *pente  : Jeu - je jeu a modifer - Donnee Resultat                                                                                       */
/* ligne   : Entier - ligne de la position du pion - Donnee                                                                                 */
/* colonne : Entier - colonne de la position du pion - Donnee                                                                               */
/* joueur : Chaîne de caractères - joueur actuel qui vient de placé le pion - Locale                                                        */
/* adversaire : Chaîne de caractères - joueur adverse (pas son tour) - Locale                                                               */
/********************************************************************************************************************************************/
void verif_captures(Jeu *pente, int ligne, int colonne)
{
    char joueur;
    char adversaire;

    if (pente -> tour == 1)
    {
        joueur = 'X';
        adversaire = 'O';
    }else
    {
        joueur = 'O';
        adversaire = 'X';
    }

    int directions[8][2] = {
        {0, 1},   // Droite
        {0, -1},  // Gauche
        {1, 0},   // Bas
        {-1, 0},  // Haut
        {1, 1},   // Diagonale Bas Droite
        {-1, -1}, // Diagonale Haut Gauche
        {1, -1},  // Diagonale Bas Gauche
        {-1, 1}   // Diagonale Haut Droite
    };

    for (int d = 0; d < 8; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        int x1 = ligne + dx, y1 = colonne + dy;
        int x2 = ligne + 2 * dx, y2 = colonne + 2 * dy;
        int x3 = ligne + 3 * dx, y3 = colonne + 3 * dy;
        if (x1 >= 0 && x1 < A && y1 >= 0 && y1 < A &&
            x2 >= 0 && x2 < A && y2 >= 0 && y2 < A &&
            x3 >= 0 && x3 < A && y3 >= 0 && y3 < A &&
            pente->plateau[x1][y1] == adversaire &&
            pente->plateau[x2][y2] == adversaire &&
            pente->plateau[x3][y3] == joueur)
        {
            pente->plateau[x1][y1] = '.';
            pente->plateau[x2][y2] = '.';
            if (joueur == 'X')
            {
                pente->scoreX += 2;
            } else
            {
                pente->scoreO += 2;
            }
        }
    }
}

/***************************************************************************************************************/
/* verif_alignement : fonction pour verifier l'alignenment de 5 pions de meme symbole dans tous les directions */
/* pente : Jeu - Le jeu qu'on verifie - Donnee                                                                 */
/* symbole : Chaîne de caractères - Le joueur qui vient de placer un pion - Locale                             */
/***************************************************************************************************************/

float verif_alignement (Jeu pente)
{
    char symbole ;
    if (pente.tour == 1)
    {
        symbole = 'X';
    }else
    {
        symbole = 'O';
    }
    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < A; j++)
        {
            if (pente.plateau[i][j] == symbole)
            {
                // Alignement horizontal
                if (j <= A - 5 && pente.plateau[i][j+1] == symbole &&
                    pente.plateau[i][j+2] == symbole && pente.plateau[i][j+3] == symbole &&
                    pente.plateau[i][j+4] == symbole)
                    {
                        return 1;
                    }

                //Alignement vertical
                if (i <= A-5 && pente.plateau[i+1][j] == symbole && pente.plateau[i+2][j] == symbole &&
                    pente.plateau[i+3][j] == symbole && pente.plateau[i+4][j])
                    {
                        return 1;
                    }

                //Alignement diagonal (descendant)
                if (i <= A-5 && j <= A-5 && pente.plateau[i+1][j+1] == symbole &&
                    pente.plateau[i+2][j+2] == symbole && pente.plateau[i+3][j+3] == symbole &&
                    pente.plateau[i+4][j+4] == symbole)
                    {
                        return 1;
                    }

                //Alignement diagonal (ascendant)
                if (i >= 4 && j <= A-5 && pente.plateau[i-1][j+1] == symbole && pente.plateau[i-2][j+2] == symbole &&
                    pente.plateau[i-3][j+3] == symbole && pente.plateau[i-4][j+4] == symbole)
                    {
                        return 1;
                    }
            }
        }
    }
    return 0;
}
/**************************************************************************************************************************/
/* tour_joueur : Action qui alterne le jeu et donne au joueur actif la main pour jouer, met a jour le plateau,            */
/* verifie les conditions de victoire et termine le jeu en cas de victoire ou abandon                                     */
/* *pente : Jeu - Donnee-Resultat                                                                                         */
/* *fini : Entier - Égale à 1 si la partie doit être terminéé, sinon sa valeur change pas et on continue - Donee-Resultat */
/* ligne : Entier - Numéro de ligne sur le plateau - Locale                                                               */
/* colonne : Entier - Numéro de colonne sur le plateau - Locale                                                           */
/* joueur : Chaîne de caractères - Joueur actuel qui vient de placé le pion - Locale                                      */
/* adversaire : Chaîne de caractères - joueur adverse (pas son tour) - Locale                                             */
/**************************************************************************************************************************/
void tour_joueur(Jeu *pente, int *fini)
{
    int ligne;
    int colonne;
    char joueur;
    char adversaire;

    if (pente->tour == 1)
    {
        joueur = 'X';
        adversaire = 'O';
    }
    else
    {
        joueur = 'O';
        adversaire = 'X';
    }

    if (pente->scoreO >= 10)
    {
        affichage_plateau(*pente);
        printf("Joueur O gagne par captures\n");
        *fini = 1;
    }
    else if (pente->scoreX >= 10)
    {
        affichage_plateau(*pente);
        printf("Joueur X gagne par captures\n");
        *fini = 1;
    }

    printf("Joueur de symbole %c: Indiquez l'indice (ligne, colonne) où vous voulez placer votre pion (entrez 0,0 pour abandonner).\n", joueur);
    scanf("%d,%d", &ligne, &colonne);

    if (ligne == 0 && colonne == 0)
    {
        printf("Le joueur %c a abandonné et le joueur %c a gagné \n", joueur, adversaire);
        *fini = 1;
    }

    if (ligne < 1 || ligne > A || colonne < 1 || colonne > A ||
        pente->plateau[ligne - 1][colonne - 1] != '.')
    {
        if(ligne != 0 || colonne != 0)
        {
            printf("Veuillez réessayer. \n");
        }
    }
    else
    {
        pente->plateau[ligne - 1][colonne - 1] = joueur;
        verif_captures(pente, ligne - 1, colonne - 1);
    }

    if (verif_alignement(*pente))
    {
        affichage_plateau(*pente);
        printf("Le joueur portant le symbole %c a gagné par alignement \n", joueur);
        *fini = 1;
    }

    pente->tour *= -1;
}

/***************************************************************/
/* Fonction principale                                         */
/* fini : Entier - Permet de finir la partie - Locale          */
/***************************************************************/
int main()
{
    Jeu pente;
    init_jeu(&pente);

    int fini = 0;
    while (!fini)
    {
        affichage_plateau(pente);
        tour_joueur(&pente, &fini);
    }

    return 0;
}

