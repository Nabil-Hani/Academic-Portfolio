// Ce code s'exécute automatiquement une fois que la page HTML a été entièrement chargée.
// Cela garantit que tous les éléments de la page sont prêts à être manipulés via JavaScript.
document.addEventListener("DOMContentLoaded", function () {
    console.log("Page chargée.");
});

/****************************************************************************************************************************/
/* Fonction qui gère le chargement et le traitement des fichiers CSV.                                                       */
/* Elle vérifie d'abord si les deux fichiers ont été sélectionnés, puis les lit et les traite via la bibliothèque PapaParse.*/
/****************************************************************************************************************************/

function traitement() {

    // Récupère le premier fichier sélectionné dans l'élément input ayant l'ID 'fichierMetropole'.
    let fichierMetropole = document.getElementById('fichierMetropole').files[0];

    // Récupère le premier fichier sélectionné dans l'élément input ayant l'ID 'fichierReunion'.
    let fichierReunion = document.getElementById('fichierReunion').files[0];

    // Vérifie si les deux fichiers sont bien sélectionnés. Si l'un des fichiers manque, affiche une alerte et arrête l'exécution.
    if (!fichierMetropole || !fichierReunion) {
        alert("Veuillez charger les deux fichiers CSV.");
        return;
    }

    // Utilisation de la bibliothèque PapaParse pour lire et analyser le fichier Métropole.
    Papa.parse(fichierMetropole, {
        download: true,    // Permet de traiter les fichiers localement sans envoi à un serveur
        header: true,      // Indique que la première ligne du fichier contient les noms des colonnes
        dynamicTyping: true,  // Convertit automatiquement les chaînes de caractères représentant des nombres en valeurs numériques
        complete: function (resultatsMetropole) {     // Fonction appelée une fois que le fichier Métropole est entièrement analysé

             // Une fois le fichier Métropole chargé, on analyse ensuite le fichier Réunion.

            Papa.parse(fichierReunion, {
                download: true,
                header: true,
                dynamicTyping: true,
                complete: function (resultatsReunion) {    // Fonction appelée une fois que le fichier Réunion est entièrement analysé

                    // Affiche la section "dashboard" qui contient les graphiques (elle est initialement cachée).
                    document.getElementById("dashboard").style.display = "block";

                    // Appelle la fonction qui génère les graphiques à partir des données analysées des deux fichiers.
                    genererGraphiques(resultatsMetropole.data, resultatsReunion.data);
                }
            });
        }
    });
}



/*******************************************************************************************************************************************************************************************************************************/


function genererGraphiques(donneesMetropole, donneesReunion) {
    console.log("Données chargées :", donneesMetropole, donneesReunion);

    /******************************************************************************************************************************/
    /* Fonction permettant de calculer la répartition des types de ménages.                                                       */
    /* Elle extrait le nombre total de ménages, ainsi que ceux composés d'une seule personne et ceux de 5 personnes ou plus.      */
    /* La catégorie "Autres" est obtenue en soustrayant les deux premiers groupes du total.                                       */
    /* donnees - Tableau contenant les données des ménages.                                                                       */
    /* On va afficher 2 camemberts contenant le nombre de ménages pour chaque catégorie [1 personne, 5 personnes ou plus, Autres].*/
    /******************************************************************************************************************************/

    function calculerMenages(donnees) {

        // Calcul du nombre total de ménages
        let total_menages = donnees.reduce((somme, ligne) => somme + parseInt(ligne.men || 0), 0);

        // Nombre de ménages composés d'une seule personne
        let menage1 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.men_1ind || 0), 0);

        // Nombre de ménages composés de 5 personnes ou plus
        let menage5 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.men_5ind || 0), 0);

        // Calcul du reste des ménages en soustrayant les deux catégories du total
        let autres = total_menages - (menage1 + menage5);

        return [menage1, menage5, autres];
    }

    // Création des données pour faire un camembert représentant la répartition des ménages
    let diagrammeMenages = [{
        values: calculerMenages(donneesMetropole),    // Données pour la Métropole
        labels: ["1 personne", "5 personnes ou plus", "Autres"], // Catégories
        title: { text: "Métropole", font: { size: 14 } },       // Titre du graphique
        type: "pie",      // Type de graphique
        name: "Métropole",
        domain: { column: 0 } // Positionnement dans la grille du graphique (on va la mettre en premier)
    }, {
        values: calculerMenages(donneesReunion),     // Données pour la Réunion
        labels: ["1 personne", "5 personnes ou plus", "Autres"],
        title: { text: "Réunion", font: { size: 14 } },
        type: "pie",
        name: "Réunion",
        domain: { column: 1 }     // On va la placer en deuxième
    }];

    // Mise en page
    let disposition1 = {
        title: { text: "Répartition des ménages", font: { size: 16 } },    // Titre principal
        height: 420,      // Hauteur du graphique
        width: 480,     // Largeur du graphique
        grid: { rows: 1, columns: 2 },  // Disposition des graphiques en 1 ligne et 2 colonnes
        margin: { l: 30, r: 30, t: 90, b: 0 },   // Marges
        showlegend: true    // Affichage de la légende
    };

    // Génération et affichage du graphique dans "chart1"
    Plotly.newPlot("chart1", diagrammeMenages, disposition1);


/*******************************************************************************************************************************************************************************************************************************/


    /******************************************************************************************************************************/
    /* Fonction permettant de calculer la répartition des individus par tranche d'âge.                                            */
    /* Elle extrait le nombre total d'individus ainsi que ceux appartenant à différentes tranches d'âge prédéfinies.              */
    /* Chaque catégorie est calculée en extrayant le total d'individus pour une tranche d'âge spécifique.                         */
    /* La fonction retourne un tableau contenant les proportions d'individus pour chaque tranche d'âge.                           */
    /* On va afficher cela sur un histogramme                                                                                     */
    /******************************************************************************************************************************/

    function calculeage(donnees) {
        let indTotal = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind || 0), 0);
        let ind0 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_0_3 || 0), 0);
        let ind4 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_4_5 || 0), 0);
        let ind6 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_6_10 || 0), 0);
        let ind11 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_11_17 || 0), 0);
        let ind18 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_18_24 || 0), 0);
        let ind25 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_25_39 || 0), 0);
        let ind40 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_40_54 || 0), 0);
        let ind55 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_55_64 || 0), 0);
        let ind65 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_65_79 || 0), 0);
        let ind80 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.ind_80p || 0), 0);
        return [ind0 / indTotal, ind4 / indTotal, ind6 / indTotal, ind11 / indTotal, ind18 / indTotal, ind25 / indTotal, ind40 / indTotal, ind55 / indTotal, ind65 / indTotal, ind80 / indTotal]
    }

    // Création d'un diagramme en barres pour représenter la répartition des groupes d'âge
    let diagrammeAges = [
        { x: ["0-3ans", "4-5ans", "6-10ans", "11-17ans", "18-24ans", "25-39ans", "40-54ans", "55-64ans", "65-79ans", "+80ans"], y: calculeage(donneesMetropole), type: "bar", name: "Métropole" },
        { x: ["0-3ans", "4-5ans", "6-10ans", "11-17ans", "18-24ans", "25-39ans", "40-54ans", "55-64ans", "65-79ans", "+80ans"], y: calculeage(donneesReunion), type: "bar", name: "Réunion" }
    ];
    Plotly.newPlot("chart2", diagrammeAges, { title: "Répartition des groupes d'âge" });


/*******************************************************************************************************************************************************************************************************************************/



    /******************************************************************************************************************************/
    /* Fonction permettant de calculer la répartition des logements construits en fonction de leur période de construction.       */
    /* Elle extrait le nombre total de logements construits et les répartit en quatre catégories temporelles :                    */
    /* - Avant 1945                                                                                                               */
    /* - Entre 1945 et 1970                                                                                                       */
    /* - Entre 1970 et 1990                                                                                                       */
    /* - Après 1990                                                                                                               */
    /* La fonction retourne un tableau contenant les proportions de logements dans chaque catégorie.                              */
    /* On va afficher ça sur un graphique d'évolution                                                                             */
    /******************************************************************************************************************************/


    function calculeLogements(donnees) {

        // Calcul du nombre total de logements pour chaque période
        let log45 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_av45 || 0), 0);
        let log70 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_45_70 || 0), 0);
        let log90 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_70_90 || 0), 0);
        let log2000 = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_ap90 || 0), 0);
        let loginc = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_inc || 0), 0);

        // Calcul du total des logements recensés
        let logTotal = log45 + log70 + log90 + log2000 + loginc;

        // Retourne un tableau des proportions de logements construits pour chaque période
        return [log45 / logTotal, log70 / logTotal, log90 / logTotal, log2000 / logTotal]
    }

    // Création d'un graphique en courbes d'évolution pour représenter l'évolution des logements construits par période
    let diagrammeLogements = [
        { x: ["avant 1945", "1945-1970", "1970-1990", "après 1990"], y: calculeLogements(donneesMetropole), type: "scatter", mode: "lines", name: "Métropole" },
        { x: ["avant 1945", "1945-1970", "1970-1990", "après 1990"], y: calculeLogements(donneesReunion), type: "scatter", mode: "lines", name: "Réunion" }
    ];
    Plotly.newPlot("chart3", diagrammeLogements, { title: "Évolution des logements construits" });




/*******************************************************************************************************************************************************************************************************************************/


    /******************************************************************************************************************************/
    /* Fonction permettant de calculer le pourcentage de ménages en situation de pauvreté.                                        */
    /* Elle extrait le nombre total de ménages ainsi que ceux en situation de pauvreté et calcule leur proportion.                */
    /* Si aucun ménage n'est recensé, le pourcentage est défini à 0 pour éviter une division par zéro.                            */
    /******************************************************************************************************************************/

    function pourcentage_pauvrete(donnees) {
        let total_menages = donnees.reduce((somme, ligne) => somme + (ligne.men || 0), 0);
        let menages_pauvres = donnees.reduce((somme, ligne) => somme + (ligne.men_pauv || 0), 0);
        let pourcentage = total_menages > 0 ? (menages_pauvres / total_menages) * 100 : 0;

        console.log(`Pourcentage de pauvreté calculé : ${pourcentage}%`);
        return pourcentage;
    }


    /******************************************************************************************************************************/
    /* Fonction permettant d'afficher les indicateurs de taux de pauvreté sous forme de jauges animées.                           */
    /* Cette fonction récupère les pourcentages de pauvreté pour la Métropole et la Réunion, puis les affiche avec FluidMeter.    */
    /* Chaque jauge est colorée différemment pour chaque région (Vert pour la Métropole, Bleu pour La Réunion).                   */
    /* donneesMetropole - Données des ménages pour la Métropole.                                                                  */
    /* donneesReunion - Données des ménages pour La Réunion.                                                                      */
    /******************************************************************************************************************************/

    function FluidMeters(donneesMetropole, donneesReunion) {
        let pauvrete_Metropole = pourcentage_pauvrete(donneesMetropole);
        let pauvrete_Reunion = pourcentage_pauvrete(donneesReunion);


        // Définition des indicateurs FluidMeter pour chaque région
        let fluid_meter = [
            { id: "fluidMeterMetropole", pourcentage: pauvrete_Metropole, color: "#228B22" }, // Vert pour la Métropole
            { id: "fluidMeterReunion", pourcentage: pauvrete_Reunion, color: "#1E90FF" } // Bleu pour la Réunion
        ];


        // Initialisation des fluid meters avec les données calculées
        fluid_meter.forEach(m => {
            let f = new FluidMeter();
            f.init({
                targetContainer: document.getElementById(m.id),
                fillPercentage: m.pourcentage,
                options: {
                    size: 150,
                    borderWidth: 10,
                    foregroundFluidLayer: { fillStyle: m.color },
                    backgroundFluidLayer: { fillStyle: "#d3d3d3" },
                    fontSize: "25px",
                    fontFamily: "Arial",
                    fontFillStyle: "white",
                    drawBubbles: true
                }
            });
        });
    }

    // Exécution de la fonction pour afficher les jauges avec les données chargées
    FluidMeters(donneesMetropole, donneesReunion);



/*******************************************************************************************************************************************************************************************************************************/


    /*******************************************************************************************************************************/
    /* Fonction permettant de calculer la surface moyenne des logements en fonction de la taille du terrain.                       */
    /* Chaque logement est classé dans l'une des cinq catégories suivantes en fonction de la taille de son terrain (en m2) :       */
    /* - 200m2, 1000m2, 2000m2, 4000m2, 8000m2.                                                                                    */
    /* La fonction calcule la somme totale des surfaces pour chaque catégorie et les divise par le nombre total de logements       */
    /* afin d'obtenir une moyenne par catégorie.                                                                                   */
    /* donnees - Tableau contenant les données des logements.                                                                      */
    /* On va afficher un graphique en barres contenant la surface moyenne des logements pour chaque catégorie de taille de terrain */
    /*******************************************************************************************************************************/


    function calculesurface(donnees) {

        // Variables locales pour compter le nombre de logements par catégorie de taille de terrain
        let i1000 = 0;
        let i2000 = 0;
        let i4000 = 0;
        let i8000 = 0;
        let i200 = 0;

        // Variables locales pour stocker la somme totale des surfaces des logements dans chaque catégorie
        let surf1000 = 0;
        let surf2000 = 0;
        let surf4000 = 0;
        let surf8000 = 0;
        let surf200 = 0;

        // On va parcourir toutes les lignes de données
        for (let i = 0; i < donnees.length; i++) {
            let ligne = donnees[i];
            let tmaille = parseFloat(ligne["tmaille"] || 0);  // Taille du terrain en m2
            let menSurf = parseFloat(ligne["men_surf"] || 0);  // Surface du logement

            // Répartition des logements par taille de terrain
            if (tmaille === 1000) {
                i1000++;
                surf1000 += menSurf;
            } else if (tmaille === 2000) {
                i2000++;
                surf2000 += menSurf;
            } else if (tmaille === 4000) {
                i4000++;
                surf4000 += menSurf;
            } else if (tmaille === 8000) {
                i8000++;
                surf8000 += menSurf;
            } else if (tmaille === 200) {
                i200++;
                surf200 += menSurf;
            }
        }

        // Calcul du total des logements recensés dans les différentes catégories
        let itot = i1000 + i2000 + i4000 + i8000 + i200;

        // On retourne un tableau contenant la surface moyenne des logements pour chaque catégorie
        return [surf200 / itot, surf1000 / itot, surf2000 / itot, surf4000 / itot, surf8000 / itot];
    }

    // Création du graphique en barres pour comparer la surface moyenne des logements entre Métropole et Réunion
    let surface = [
        { x: ["200m", "1000m", "2000m", "4000m", "8000m"], y: calculesurface(donneesMetropole), type: "bar", name: "Métropole" },
        { x: ["200m", "1000m", "2000m", "4000m", "8000m"], y: calculesurface(donneesReunion), type: "bar", name: "Réunion" }
    ];

    Plotly.newPlot("chart5", surface, { title: "Surface de logement par rapport au coté du carré" });



/*******************************************************************************************************************************************************************************************************************************/


    /******************************************************************************************************************************/
    /* Fonction permettant de calculer le revenu moyen par individu et par ménage.                                                */
    /* Elle extrait le revenu total de la population et le divise respectivement par le nombre d'individus et de ménages.         */
    /* Cette fonction permet de comparer le revenu moyen par individu et par ménage entre la Métropole et La Réunion.             */
    /* donnees - Tableau contenant les données sur les revenus des individus et des ménages.                                      */
    /* Nous aidera pour l'affichage des jauges                                                                                    */
    /******************************************************************************************************************************/

    function calculerRevenu(donnees) {

        // Somme totale des revenus individuels
        let revenu_total = donnees.reduce((somme, ligne) => somme + parseFloat(ligne.ind_snv || 0), 0);

        // Nombre total d'individus et de ménages
        let revenu_individuel = donnees.reduce((somme, ligne) => somme + parseFloat(ligne.ind || 0), 0);
        let revenu_menage = donnees.reduce((somme, ligne) => somme + parseFloat(ligne.men || 0), 0);

        // Retourne les revenus moyens par individu et par ménage
        return {
            parInd: revenu_total / revenu_individuel,
            parMen: revenu_total / revenu_menage
        };
    }

    // Calcul des revenus moyens pour la Métropole et La Réunion
    let revenuMetropole = calculerRevenu(donneesMetropole);
    let revenuReunion = calculerRevenu(donneesReunion);


    /******************************************************************************************************************************/
    /* Fonction permettant d'afficher des jauges représentant les revenus moyens par individu et par ménage.                      */
    /* Elle génère quatre jauges distinctes pour afficher les revenus moyens en Métropole et à La Réunion.                        */
    /* Chaque jauge affiche un titre et une échelle de valeurs allant de 0 à 100 000 euros.                                       */
    /* revenuMetropole - Objet contenant les revenus moyens pour la Métropole.                                                    */
    /* revenuReunion - Objet contenant les revenus moyens pour La Réunion.                                                        */
    /******************************************************************************************************************************/

    function graphiquesRevenu(revenuMetropole, revenuReunion) {
        const maxValue = 100000;   // Plafond des jauges en euros

        // Définition des indicateurs pour les jauges de revenus
        let revenu = [
            {
                type: "indicator",
                mode: "gauge+number",
                value: revenuMetropole.parInd,
                title: { text: "Métropole - Individu", font: { size: 12 } },
                gauge: { axis: { range: [0, maxValue], showticklabels: false } },
                domain: { row: 0, column: 0 }
            },
            {
                type: "indicator",
                mode: "gauge+number",
                value: revenuMetropole.parMen,
                title: { text: "Métropole - Ménage", font: { size: 12 } },
                gauge: { axis: { range: [0, maxValue], showticklabels: false } },
                domain: { row: 0, column: 1 }
            },
            {
                type: "indicator",
                mode: "gauge+number",
                value: revenuReunion.parInd,
                title: { text: "Réunion - Individu", font: { size: 12 } },
                gauge: { axis: { range: [0, maxValue], showticklabels: false } },
                domain: { row: 1, column: 0 }
            },
            {
                type: "indicator",
                mode: "gauge+number",
                value: revenuReunion.parMen,
                title: { text: "Réunion - Ménage", font: { size: 12 } },
                gauge: { axis: { range: [0, maxValue], showticklabels: false } },
                domain: { row: 1, column: 1 }
            }
        ];

        let disposition2 = {
            title: { text: "Revenu Moyen par Individu et par Ménage (en euros)", font: { size: 14 } },
            grid: { rows: 2, columns: 2, pattern: "independent", roworder: "top to bottom", columngap: 0.2 },
            margin: { t: 30, b: 30, l: 30, r: 30 },
            height: 300,
            width: 400

        };

        Plotly.newPlot("chart6", revenu, disposition2);
    }

    // Génération des graphiques de revenus
    graphiquesRevenu(revenuMetropole, revenuReunion);



/*******************************************************************************************************************************************************************************************************************************/


    /*********************************************************************************************************************************/
    /* Fonction permettant de calculer la répartition des types de logements.                                                        */
    /* Elle extrait le nombre total de logements sociaux, de maisons individuelles et de logements collectifs à partir des données.  */
    /* Ces informations sont ensuite utilisées pour comparer la répartition des types de logements entre la Métropole et La Réunion. */
    /* donnees - Tableau contenant les données des logements.                                                                        */
    /* On affichera un camembert contenant le nombre total de logements sociaux, maisons individuelles et logements collectifs.      */
    /*********************************************************************************************************************************/

    function calcul_logement(donnees) {

        // Nombre total de logements sociaux
        let total_sociaux = donnees.reduce((somme, ligne) => somme + parseInt(ligne.log_soc || 0), 0);

        // Nombre total de maisons individuelles
        let total_maison = donnees.reduce((somme, ligne) => somme + parseInt(ligne.men_mais || 0), 0);

        // Nombre total de logements collectifs
        let total_collectif = donnees.reduce((somme, ligne) => somme + parseInt(ligne.men_coll || 0), 0);

        // Retourne un tableau avec les trois types de logements
        return [total_sociaux, total_maison, total_collectif];
    }

    // Création des camemberts pour comparer la répartition des types de logements
    var logement = [{
        values: calcul_logement(donneesMetropole),
        labels: ['Sociaux', 'Maison', 'Collectif'],
        title: { text: "Métropole", font: { size: 14 } },
        type: 'pie',
        name: 'Métropole',
        domain: { column: 0 }
    }, {
        values: calcul_logement(donneesReunion),
        labels: ['Sociaux', 'Maison', 'Collectif'],
        title: { text: "Réunion", font: { size: 14 } },
        type: 'pie',
        name: 'Réunion',
        domain: { column: 1 },
    }];
    var disposition3 = {
        title: {
            text: 'Répartition des types de logement', font: {size: 20}
        },
        height: 400,
        width: 450,
        grid: { rows: 1, columns: 2 },
        showlegend: true
    };
    Plotly.newPlot("chart7", logement, disposition3);


/*******************************************************************************************************************************************************************************************************************************/
    let graphiques = ["chart1", "chart2", "chart3", "chart4", "chart5", "chart6", "chart7"];
    graphiques.forEach(id => document.getElementById(id).classList.add("chart-container"));
}
