#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphe.h"
#include "chemin.h"

/******************************************************************************************************************************************************************************************************************************/




/********************************************************************************************************/
/* ajouterArc : Procédure permettant de créer un arc et de l’ajouter au graphe G                        */
/*                                                                                                      */
/*    G           : Graphe* - Pointeur vers le graphe concerné          (Donnée)                        */
/*    origine     : entier  - Identifiant du sommet d’origine de l’arc  (Donnée)                        */
/*    destination : entier  - Identifiant du sommet d’arrivée de l’arc  (Donnée)                        */
/*    capacite    : entier  - Capacité associée à l’arc                 (Donnée)                        */
/*                                                                                                      */
/* Cette procédure crée un nouvel arc de origine vers destination avec une capacité donnée.             */
/* Elle l’insère en tête de la liste des successeurs du sommet origine.                                 */
/* Le champ flot est initialisé à 0, et le pointeur reverse à NIL.                                      */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*    arc1 : Arc* - Pointeur vers la nouvelle structure d’arc allouée                                   */
/********************************************************************************************************/

void ajouterArc(struct Graphe* G, int origine, int destination, int capacite) {
    struct Arc* arc1 = malloc(sizeof(struct Arc));
    arc1->dest = destination;
    arc1->capa = capacite;
    arc1->flot = 0;
    arc1->reverse = NIL;
    arc1->suivant = G->sommets[origine].successeurs;
    G->sommets[origine].successeurs = arc1;
}




/******************************************************************************************************************************************************************************************************************************/




/****************************************************************************************************************/
/* buildGraph : Procédure permettant de construire un graphe à partir d’un fichier DIMACS                       */
/*                                                                                                              */
/*        G            : Graphe* - Pointeur vers la structure Graphe à initialiser           (Donnée/Resultat)  */
/*        source       : int*    - Pointeur vers la variable contenant l’identifiant source  (Donnée/Resultat)  */
/*        puit         : int*    - Pointeur vers la variable contenant l’identifiant puit    (Donnée/Resultat)  */
/*                                                                                                              */
/* Cette procédure lit les lignes d’un fichier au format DIMACS via l’entrée standard,                          */
/* initialise la structure du graphe G, et place les informations liées à la source et au puit.                 */
/* Les arcs sont ajoutés un par un via la fonction ajouterArc.                                                  */
/*                                                                                                              */
/* Variables locales :                                                                                          */
/*    n, m        : int   - Nombre de sommets et nombre d’arcs dans le graphe                                   */
/*    nb_arcs     : int   - Compteur pour les arcs lus                                                          */
/*    lettre      : char  - Caractère lu pour identifier les lignes (p, a, n, c, etc.)                          */
/*    trouve_p    : bool  - Indicateur pour s’assurer que la ligne p a été trouvée                              */
/*    node        : int   - Identifiant d’un sommet déclaré comme source ou puit                                */
/*    type        : char  - Type associé à un sommet (s pour source, t pour puit)                               */
/*    origine     : int   - Sommet de départ d’un arc                                                           */
/*    destination : int   - Sommet d’arrivée d’un arc                                                           */
/*    capacite    : int   - Capacité associée à un arc                                                          */
/****************************************************************************************************************/

void buildGraph(struct Graphe* G, int* source, int* puit) {
    int n = 0, m = 0;
    int nb_arcs = 0;
    char lettre;
    int trouve_p = 0;

    // Lire jusqu’à trouver la ligne 'p'
    while (!trouve_p) {
        lettre = getchar();
        if (lettre == 'c') {
            while ((lettre = getchar()) != '\n');
        } else if (lettre == 'p') {
            scanf("%d %d", &n, &m);
            while ((lettre = getchar()) != '\n');
            trouve_p = 1;
        } else {
            while ((lettre = getchar()) != '\n');
        }
    }

    G->nb_sommets = n;
    G->sommets = malloc(n * sizeof(struct Sommet));
    for (int i = 0; i < n; i++) {
        G->sommets[i].successeurs = NULL;
    }

    while (nb_arcs < m) {
        lettre = getchar();

        if (lettre == 'c') {
            while ((lettre = getchar()) != '\n');
        } else if (lettre == 'n') {
            int node;
            char type;
            scanf("%d %c", &node, &type);
            while ((lettre = getchar()) != '\n');

            if (type == 's') *source = node - 1;
            else if (type == 't') *puit = node - 1;

        } else if (lettre == 'a') {
            int origine, destination, capacite;
            scanf("%d %d %d", &origine, &destination, &capacite);
            origine--; destination--;
            ajouterArc(G, origine, destination, capacite);
            nb_arcs++;
            while ((lettre = getchar()) != '\n');
        } else {
            while ((lettre = getchar()) != '\n');
        }
    }
}



/******************************************************************************************************************************************************************************************************************************/



/********************************************************************************************************/
/* buildRG : Fonction qui construit le graphe résiduel RG à partir du graphe initial G                  */
/*                                                                                                      */
/*             G : Graphe* - Pointeur vers le graphe initial (réseau avec flots initiaux)   (Donnée)    */
/*                                                                                                      */
/*  Retourne :                                                                                          */
/*      struct Graphe* - Pointeur vers le graphe résiduel nouvellement construit    (Résultat)          */
/*                                                                                                      */
/* Le graphe résiduel est construit en copiant les sommets de G, puis en créant pour chaque arc         */
/* un arc direct (capacité résiduelle = capa - flot) et un arc inverse (capacité = flot),               */
/* avec des liens "reverse" entre les arcs directs et inverses pour faciliter la mise à jour des flots. */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*     RG           : struct Graphe* - Graphe résiduel en construction                                  */
/*     s, s1        : int - indices des sommets                                                         */
/*     a            : struct Arc* - arc courant dans G                                                  */
/*     arc_direct   : struct Arc* - arc direct créé dans RG                                             */
/*     arc_inverse  : struct Arc* - arc inverse créé dans RG                                            */
/*     capa_directe : int - capacité résiduelle directe                                                 */
/*     capa_inverse : int - capacité résiduelle inverse                                                 */
/********************************************************************************************************/

struct Graphe* buildRG(struct Graphe* G) {
    struct Graphe* RG = malloc(sizeof(struct Graphe));
    RG->nb_sommets = G->nb_sommets;
    RG->sommets = malloc(RG->nb_sommets * sizeof(struct Sommet));
    for (int s = 0; s < G->nb_sommets; s++) {
        RG->sommets[s].successeurs = NIL;
    }

    for (int s = 0; s < G->nb_sommets; s++) {
        for (struct Arc* a = G->sommets[s].successeurs; a != NIL; a = a->suivant) {
            int s1 = a->dest;
            int capa_directe = a->capa - a->flot;
            int capa_inverse = a->flot;

            // Création de l’arc direct dans RG
            struct Arc* arc_direct = malloc(sizeof(struct Arc));
            arc_direct->dest = s1;
            arc_direct->capa = capa_directe;
            arc_direct->flot = 0;
            arc_direct->suivant = RG->sommets[s].successeurs;

            // Création de l’arc inverse dans RG
            struct Arc* arc_inverse = malloc(sizeof(struct Arc));
            arc_inverse->dest = s;
            arc_inverse->capa = capa_inverse;
            arc_inverse->flot = 0;
            arc_inverse->suivant = RG->sommets[s1].successeurs;

            // Liens entre arcs inverses
            arc_direct->reverse = arc_inverse;
            arc_inverse->reverse = arc_direct;

            // Insertion dans les listes
            RG->sommets[s].successeurs = arc_direct;
            RG->sommets[s1].successeurs = arc_inverse;
        }
    }
    return RG;
}



/******************************************************************************************************************************************************************************************************************************/




/********************************************************************************************************/
/* shortestPath : Recherche du plus court chemin en nombre d'arcs dans le graphe résiduel RG            */
/*               (parcours en largeur)                                                                  */
/*                                                                                                      */
/*             RG : struct Graphe* - Pointeur vers le graphe résiduel   (Donnée)                        */
/*              s : int         - Sommet source du chemin               (Donnée)                        */
/*              p : int         - Sommet puits (destination)            (Donnée)                        */
/*                                                                                                      */
/* Retourne :                                                                                           */
/*      struct chemin - chemin le plus court trouvé sous forme d’un tableau de sommets  (Résultat)      */
/*                                                                                                      */
/* Le chemin est trouvé en utilisant une recherche en largeur sur RG, marquant les sommets              */
/* visités et mémorisant leurs prédécesseurs pour reconstruire le chemin.                               */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*    Mark       : bool* - tableau de marquage des sommets visités                                      */
/*    pred       : int*  - tableau des prédécesseurs pour reconstruire le chemin                        */
/*    queue      : int*  - file pour la BFS                                                             */
/*    head, tail : int - indices pour gestion de la file                                                */
/*    trouve     : bool - indique si le chemin a été trouvé                                             */
/*    c          : struct chemin - chemin résultat                                                      */
/********************************************************************************************************/

struct chemin shortestPath(struct Graphe* RG, int s, int p) {
    bool* Mark = malloc(RG->nb_sommets* sizeof(bool));
    int* pred = malloc(RG->nb_sommets * sizeof(int));
    for (int i = 0; i < RG->nb_sommets; i++) {
        Mark[i] = false;
        pred[i] = -1;
    }
    Mark[s] = true;

    int* queue = malloc(RG->nb_sommets * sizeof(int));
    int head = 0, tail = 0;
    queue[tail++] = s;

    bool trouve = false;

    while (head < tail && !trouve) {
        int u = queue[head++];
        if (u == p) {
            trouve = true;
        } else {
            for (struct Arc* a = RG->sommets[u].successeurs; a != NULL; a = a->suivant) {
                int v = a->dest;
                if (!Mark[v] && a->capa > 0) {
                    Mark[v] = true;
                    pred[v] = u;
                    queue[tail++] = v;
                }
            }
        }
    }
    struct chemin c;
    c.taille = 0;
    c.sommets = NULL;
    if (trouve) {
        int current = p;
        while (current != -1) {
            c.taille++;
            current = pred[current];
        }

        c.sommets = malloc(c.taille * sizeof(int));
        current = p;
        for (int i = c.taille - 1; i >= 0; i--) {
            c.sommets[i] = current;
            current = pred[current];
        }
    }
    free(Mark);
    free(pred);
    free(queue);
    return c;
}




/******************************************************************************************************************************************************************************************************************************/




/********************************************************************************************************/
/* minCapa : Fonction permettant de déterminer la capacité minimale le long d’un chemin donné dans RG   */
/*                                                                                                      */
/*    G    : Graphe* - le graphe d’écart contenant les capacités actuelles des arcs        (Donnée)     */
/*    c    : chemin  - structure contenant la séquence des sommets du chemin de s à p      (Donnée)     */
/*                                                                                                      */
/* Retourne: int     - la valeur de la plus petite capacité le long du chemin              (Résultat)   */
/*                                                                                                      */
/* La fonction parcourt le tableau de sommets du chemin `c` (de s à p), pour chaque paire (u,v)         */
/* consécutive, elle recherche dans les successeurs de `u` l’arc menant à `v`.                          */
/* Si la capacité de cet arc est inférieure à la capacité minimale actuelle, on la met à jour.          */
/* À la fin, la capacité minimale trouvée est retournée. Cette valeur représente le flot maximum        */
/* qu’on peut injecter sur ce chemin sans saturer un arc.                                               */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*    u, v   : int        - identifiants des sommets consécutifs dans le chemin                         */
/*    a      : Arc*       - pointeur vers les arcs sortants de `u` dans le graphe                       */
/*    trouve : bool       - indicateur pour arrêter la recherche dès que l’arc (u,v) est trouvé         */
/*    min    : int        - capacité minimale observée le long du chemin (initialisée à une grande val) */
/********************************************************************************************************/

int minCapa(struct Graphe* G, struct chemin c) {
    int min = 1000000000; // grande valeur puisqu'on traitera des graphes avec des grandes capacités'
    for (int i = 0; i < c.taille - 1; i++) {
        int u = c.sommets[i];
        int v = c.sommets[i + 1];
        struct Arc* a = G->sommets[u].successeurs;
        bool trouve = false;
        while (a != NULL && !trouve) {
            if (a->dest == v) {
                if (a->capa < min) min = a->capa;
                trouve = true;
            } else {
                a = a->suivant;
            }
        }
    }
    return min;
}




/******************************************************************************************************************************************************************************************************************************/




/********************************************************************************************************/
/* updateFlowInRG : Action qui met à jour les capacités résiduelles du graphe résiduel G                */
/* G : Graphe*       - le graphe résiduel à modifier (Donnée-Résultat)                                  */
/* c : chemin        - le chemin de s à p sur lequel on envoie du flot (Donnée)                         */
/* k : int           - le flot à injecter sur le chemin (Donnée)                                        */
/*                                                                                                      */
/* Cette procédure parcourt chaque paire consécutive (u, v) de sommets dans le chemin `c`               */
/* (qui représente un chemin dans le graphe d’écart). Pour chaque telle paire, elle recherche dans      */
/* la liste des successeurs de `u` l’arc menant à `v`.                                                  */
/* Une fois cet arc trouvé, elle diminue sa capacité résiduelle de `k` et augmente celle de son         */
/* arc inverse de `k`, ce qui modélise le transfert de flot dans le graphe d’écart.                     */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/* - u, v : int         - identifiants des sommets consécutifs dans le chemin                           */
/* - a     : Arc*       - pointeur utilisé pour parcourir la liste des arcs sortants de `u`             */
/* - trouve: bool       - indicateur pour arrêter la recherche une fois l’arc trouvé                    */
/********************************************************************************************************/

void updateFlowInRG(struct Graphe* G, struct chemin c, int k) {
    for (int i = 0; i < c.taille - 1; i++) {
        int u = c.sommets[i];
        int v = c.sommets[i + 1];
        struct Arc* a = G->sommets[u].successeurs;
        bool trouve = false;
        while (a != NULL && !trouve) {
            if (a->dest == v) {
                a->capa -= k;
                a->reverse->capa += k;
                trouve = true;
            } else {
                a = a->suivant;
            }
        }
    }
}



/******************************************************************************************************************************************************************************************************************************/



/********************************************************************************************************/
/* updateFlowInNet : Procédure permettant de synchroniser les flots dans le graphe original G           */
/*                   à partir des capacités résiduelles présentes dans le graphe résiduel RG.           */
/*                                                                                                      */
/*    G   : Graphe* - graphe original contenant les capacités et les arcs initiaux    (Donnée/Résultat) */
/*    RG  : Graphe* - graphe résiduel après application des augmentations de flot         (Donnée)      */
/*                                                                                                      */
/* Cette procédure parcourt tous les arcs du graphe original G. Pour chaque arc (u,v), elle             */
/* recherche l'arc correspondant (u,v) dans le graphe résiduel RG, puis déduit le flot courant          */
/* comme la différence entre la capacité initiale (dans G) et la capacité résiduelle (dans RG).         */
/*                                                                                                      */
/* Le flot aG->flot est mis à jour à : aG->capa - aRG->capa.                                            */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*    s   : int    - identifiant du sommet courant du graphe original                                   */
/*    aG  : Arc*   - pointeur vers les arcs du graphe original                                          */
/*    aRG : Arc*   - pointeur vers les arcs du graphe résiduel pour comparaison                         */
/********************************************************************************************************/

void updateFlowInNet(struct Graphe* G, struct Graphe* RG) {
    for (int s = 0; s < G->nb_sommets; s++) {
        struct Arc* aG = G->sommets[s].successeurs;
        while (aG != NIL) {
            struct Arc* aRG = RG->sommets[s].successeurs;
            while (aRG != NIL) {
                if (aRG->dest == aG->dest) {
                    aG->flot = aG->capa - aRG->capa;
                    break;
                }
                aRG = aRG->suivant;
            }
            aG = aG->suivant;
        }
    }
}



/******************************************************************************************************************************************************************************************************************************/




/********************************************************************************************************/
/* afficherFlots : Procédure permettant d’afficher les flots actuels dans les arcs du graphe G.         */
/*                                                                                                      */
/*    G : Graphe* - graphe contenant les sommets et leurs arcs, avec les flots calculés     (Donnée)    */
/*                                                                                                      */
/* Cette procédure parcourt tous les sommets du graphe G. Pour chaque sommet s, elle parcourt sa liste  */
/* d’adjacence (les arcs sortants), et affiche pour chaque arc (s -> v) la valeur du flot actuel        */
/* (a->flot) ainsi que la capacité de l’arc (a->capa).                                                  */
/*                                                                                                      */
/* Le résultat est imprimé sur la sortie standard sous forme : "(u -> v) : flot = x / y"                */
/*                                                                                                      */
/* Variables locales :                                                                                  */
/*    s : int    - identifiant du sommet courant du graphe                                              */
/*    a : Arc*   - pointeur vers un arc sortant du sommet s                                             */
/********************************************************************************************************/

void afficherFlots(struct Graphe* G) {
    printf("Flux dans les arcs du graphe :\n");
    for (int s = 0; s < G->nb_sommets; s++) {
        for (struct Arc* a = G->sommets[s].successeurs; a != NIL; a = a->suivant) {
            printf("(%d -> %d) : flot = %d / %d\n", s, a->dest, a->flot, a->capa);
        }
    }
}



/******************************************************************************************************************************************************************************************************************************/



/*********************************************************************************************************/
/* ecrireResultatDansFichier : Procédure permettant d’écrire les résultats de l’algorithme dans un       */
/*                             fichier texte, incluant le flot maximal et les flots sur chaque arc.      */
/*                                                                                                       */
/*    G            : Graphe*   - graphe contenant les sommets et arcs avec les flots calculés   (Donnée) */
/*    flotMaximal  : int       - valeur du flot maximal obtenu par l’algorithme                 (Donnée) */
/*    nomFichier   : const char* - chemin du fichier dans lequel écrire les résultats           (Donnée) */
/*                                                                                                       */
/* La procédure ouvre le fichier indiqué en écriture, puis écrit sur la première ligne le flot maximal.  */
/* Ensuite, elle parcourt chaque sommet et ses arcs sortants pour écrire les arcs ayant un flot > 0.     */
/* Chaque ligne du fichier indique un arc et la valeur de son flot : "u -> v | flot = x".                */
/*                                                                                                       */
/* Si le fichier ne peut pas être ouvert, un message d’erreur est affiché via perror.                    */
/*                                                                                                       */
/* Variables locales :                                                                                   */
/*    fichier : FILE* - pointeur vers le fichier ouvert en écriture                                      */
/*    u       : int   - identifiant du sommet courant                                                    */
/*    a       : Arc*  - pointeur vers les arcs sortants du sommet courant                                */
/*********************************************************************************************************/

void ecrireResultatDansFichier(struct Graphe* G, int flotMaximal, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier de sortie");
        return;
    }

    fprintf(fichier, "Flot maximal : %d\n", flotMaximal);
    for (int u = 0; u < G->nb_sommets; ++u) {
        for (struct Arc* a = G->sommets[u].successeurs; a != NULL; a = a->suivant) {
            if (a->flot > 0) {
                fprintf(fichier, "%d -> %d | flot = %d / %d\n", u + 1, a->dest + 1, a->flot, a->capa);
            }
        }
    }

    fclose(fichier);
    printf("Résultats écrits dans le fichier : %s\n", nomFichier);
}



/******************************************************************************************************************************************************************************************************************************/



int main(int argc, char* argv[]) {

    if(argc!=2) {
        fprintf(stderr, "Usage: fournir un fichier DIMACS en parametre\n");
        exit(1);
    }

    const char* nomFichier = argv[1];
    struct Graphe G;
    int source = -1, puit = -1;

    buildGraph(&G, &source, &puit);

    int flot_total = 0;
    struct Graphe* RG = buildRG(&G);
    struct chemin chemin = shortestPath(RG, source, puit);

    while (chemin.taille > 0) {
        int k = minCapa(RG, chemin);
        updateFlowInRG(RG, chemin, k);
        flot_total += k;
        free(chemin.sommets);
        chemin = shortestPath(RG, source, puit);
    }

    updateFlowInNet(&G, RG);
    afficherFlots(&G);
    printf("Flot maximal trouvé : %d\n", flot_total);

    ecrireResultatDansFichier(&G, flot_total, nomFichier);

    free(chemin.sommets);
    free(RG->sommets);
    free(RG);
    free(G.sommets);
    return 0;
}
