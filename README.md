# 🎓 Nabil Hani – Engineering Academic Portfolio (Polytech Lille 2024‑2027)

This repository collects my academic deliverables from the Polytech Lille computer engineering curriculum. Each folder is a self-contained project with its own source files, datasets, and (when relevant) compiled artefacts or reports. The sections below document every project in detail so you can understand what each directory contains, how the code is structured, and how to run it.

---

## 📚 Table of Contents
1. [Algorithms & Systems Projects](#algorithms--systems-projects)
   * [Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)](#dinic-maximum-flow-solver-projet_sd_graphes)
   * [Penté Strategy Game Toolkit (`Penté/`)](#pente-strategy-game-toolkit-penté)
2. [Object-Oriented Games in Java](#object-oriented-games-in-java)
   * [Complete Minesweeper Engine & GUI (`Demineur/`)](#complete-minesweeper-engine--gui-demineur)
   * [Packaged Minesweeper Build (`Demineur_2/`)](#packaged-minesweeper-build-demineur_2)
3. [Web Engineering Projects](#web-engineering-projects)
   * [Interactive CV Website (`CV_Website/`)](#interactive-cv-website-cv_website)
   * [BI/Data Dashboard Prototype (`Projet_Data/`)](#bidata-dashboard-prototype-projet_data)
4. [Contact & License](#contact--license)

---

## Algorithms & Systems Projects

### Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)
**Languages & tooling:** ISO C99, custom data structures, `gcc`, `Makefile`, DIMACS network format

**Purpose.** Implements a full maximum-flow solver inspired by Dinic's algorithm. The code reads directed networks in DIMACS format, builds an adjacency-list representation with reverse-arc pointers, repeatedly searches for shortest augmenting paths in the residual graph, and writes the resulting flow to disk.

**Key files.**
- `Projet.c` — orchestrates the whole pipeline: parsing the DIMACS file (`buildGraph`), constructing the residual graph (`buildRG`), locating augmenting paths with BFS (`shortestPath`), updating residual capacities (`updateFlowInRG`), and synchronising flows back to the base network (`updateFlowInNet`).
- `graphe.h`, `sommet.h`, `arc.h`, `chemin.h` — define the graph structures (successor lists with `reverse` pointers) and the path representation used by the solver.
- `Makefile` — automates compilation, including `make clean` for rebuilding from scratch.
- `ReadMe.txt` — French-language run manual with sample commands and dataset descriptions.

**How it works.**
1. **Parsing:** `buildGraph` scans the DIMACS stream, initialises an array of vertices, and adds arcs through `ajouterArc`, which inserts `Arc` records at the head of the relevant successor list.
2. **Residual network:** `buildRG` clones every arc into a residual graph, creating paired forward/backward arcs whose `reverse` pointers allow $O(1)$ updates during augmentation.
3. **Augmenting paths:** `shortestPath` performs a breadth-first search to find the minimum-edge path between the source and sink in the residual graph. The returned `chemin` structure stores the vertex sequence to traverse.
4. **Flow augmentation:** `minCapa` scans the path to compute the bottleneck capacity, `updateFlowInRG` pushes that flow through the residual arcs, and `updateFlowInNet` reconciles the residual capacities with the original graph to track actual flow values.
5. **Output:** `afficherFlots` dumps arc flows to stdout while `ecrireResultatDansFichier` records the max-flow value and every positive-flow arc in the user-specified results file.

**Running the solver.**
```bash
cd Projet_SD_Graphes
make                            # builds the Projet executable with gcc
./Projet resultats_net1.txt < net1.txt
./Projet resultats_G_100_300.txt < G_100_300.max
```
Input networks should follow the DIMACS `p`, `n`, `a` syntax. The generated report lists the maximum flow followed by each saturated arc.

---

### Penté Strategy Game Toolkit (`Penté/`)
**Languages & tooling:** C (console I/O), 19×19 board data files, PDF report

**Purpose.** Provides an interactive command-line assistant for the Penté abstract strategy game (five-in-a-row with captures). It models the board, validates moves, applies capture rules, and reports the game state after each turn. Companion board files and a project report illustrate algorithmic design decisions.

**Key files.**
- `pente.c` — contains the full rules engine. Highlighted routines include:
  * `init_jeu` for zeroing the 19×19 board and resetting capture counters.
  * `verif_captures` to scan eight directions after every move and remove captured stones while updating scores.
  * `verif_alignement` to detect lines of five and declare a winner.
  * `tour_joueur` to alternate between players, request coordinates, validate inputs, apply moves, and stop the game on victory or resignation.
- `pente` — compiled executable for quick play without rebuilding.
- `pente1.txt` … `pente7.txt` — sample positions used during testing and evaluation.
- `Algorithmique et Programmation - Rapport.pdf` — detailed write-up (in French) covering heuristics, complexity analysis, and lessons learned.

**Usage.**
```bash
cd Penté
./pente                 # launch the interactive CLI version
# or recompile if needed
gcc -o pente pente.c
```
The program prints a labelled grid, tracks the capture tally (`scoreX`/`scoreO`), and announces a winner whenever an alignment or capture threshold is reached.

---

## Object-Oriented Games in Java

### Complete Minesweeper Engine & GUI (`Demineur/`)
**Languages & tooling:** Java 17+, Swing, custom exceptions

**Purpose.** Demonstrates object-oriented design by splitting a full Minesweeper implementation into engine, GUI, and exception layers. The engine guarantees rules correctness, while the Swing interface handles user input, configuration dialogs, and status displays.

**Architecture overview.**
- **Game engine (`lib/`):**
  * `Demineur` manages the grid, lazy bomb placement, recursive flood-fill (`propagationRecursive`), move counting, and victory detection.
  * `AbstractCell`, `StandardCell`, and `BombCell` encapsulate state transitions (revealed, flagged, adjacent bomb counts) and enforce type-specific logic.
- **Error handling (`exceptions/`):** `InvalidMoveException`, `GameLostException`, and `GameWonException` communicate engine outcomes to the UI without coupling to Swing components.
- **Swing UI (`gui/`):**
  * `DemineurUI` boots the application, wires listeners, and reacts to engine events.
  * `SetupDialog` collects difficulty settings before starting a game.
  * `GamePanel` renders the grid, translates mouse events into engine calls, and reveals cells accordingly.
  * `TopPanel` shows timers, bomb counters, and status messages.

**Key gameplay details.**
- Bombs are placed **after** the first click (`placerBombes`) to guarantee a safe opening.
- Recursive clearing spreads through empty regions while tracking visited cells to avoid infinite loops.
- Engine exceptions bubble up to the GUI so the interface can display win/lose pop-ups and lock further interaction.

**Build & run.**
```bash
cd Demineur
javac exceptions/*.java gui/*.java lib/*.java
java gui.DemineurUI
```
The compiled game opens a Swing window where you can configure board size, play, and observe live counters.

---

### Packaged Minesweeper Build (`Demineur_2/`)
**Languages & tooling:** Java 17+, precompiled `.class` files, identical source tree to `Demineur/`

**Purpose.** Offers the same Minesweeper project but bundled with compiled classes for immediate execution—ideal for grading sessions or demonstrations when a Java compiler is unavailable.

**Contents.**
- Mirrors the `Demineur/` package structure (`gui/`, `lib/`, `exceptions/`) with both `.java` and `.class` artefacts.
- Provides ready-to-run bytecode: launching `java gui.DemineurUI` within this directory starts the game without recompilation.

**Usage.**
```bash
cd Demineur_2
java gui.DemineurUI          # uses the shipped .class files
# optionally rebuild to regenerate bytecode
javac exceptions/*.java gui/*.java lib/*.java
```
If you modify the sources, re-run `javac` to update the included class files.

---

## Web Engineering Projects

### Interactive CV Website (`CV_Website/`)
**Stack:** HTML5, CSS3, Bootstrap 5, vanilla JavaScript, Chart.js

**Purpose.** Presents a personal résumé site with multiple pages (home, CV, links, hobbies). It highlights responsive design, modular styling, and client-side interactivity for showcasing skills.

**Highlights.**
- `index.html` renders a hero section with avatar, contact links, and a collapsible Bootstrap navbar. An aside hosts buttons that inject résumé content and mini-games.
- `cv.html`, `liens.html`, and `loisirs.html` provide supplementary sections using the shared stylesheet.
- `styles.css` defines global typography, theming, and reusable utility classes in addition to Bootstrap defaults.
- `scripts.js` binds the “Afficher le CV” button to inject structured CV data, draw a doughnut chart of competencies via Chart.js, and embed a lightweight clicker mini-game.
- `assets/` contains imagery (e.g., `photo.jpg`) used across the pages.

**Preview.** Open `index.html` in a browser. The responsive layout adapts gracefully from mobile to desktop, while the injected Chart.js graphic animates skill breakdowns on demand.

---

### BI/Data Dashboard Prototype (`Projet_Data/`)
**Stack:** HTML5, CSS3, vanilla JavaScript, Plotly.js, PapaParse, SVG assets

**Purpose.** Emulates a data-analytics dashboard for socio-economic indicators by loading CSV extracts (from INSEE open data), cleaning them in the browser, and visualising results through interactive charts and gauges.

**Key features.**
- **Data ingestion (`script.js`):**
  * `traitement()` validates that both metropolitan and Réunion CSV files are selected, then parses them asynchronously with PapaParse.
  * `genererGraphiques()` dispatches to helper functions that aggregate metrics (household composition, age brackets, housing stock periods, poverty rates) and renders Plotly charts (`chart1`, `chart2`, `chart3`, `chart4`).
  * Additional helpers compute indicators for fluid-meter gauges, dynamic cards, and textual summaries.
- **Dashboard layout:**
  * `index.html`, `analyse.html`, and `indicateurs.html` split the experience into onboarding, exploratory analysis, and KPI pages.
  * `style.css` styles navigation, cards, and responsive chart containers; icons such as `revenu.png` and `pauvrete.png` reinforce the narrative.
  * `js-fluid-meter.js` drives animated dial components for KPI visualisation.
- **Datasets:** `carreaux_nivNaturel_met.csv` and `carreaux_nivNaturel_reun.csv` store the raw indicators consumed during demo sessions.

**Running the dashboard.** Serve the directory via a static HTTP server (or open the HTML files directly with a browser allowing local script access). Use the file pickers to load both CSV files and reveal the generated charts and KPI gauges.

---

## Contact & License
- **LinkedIn:** [linkedin.com/in/hani-nabil](https://www.linkedin.com/in/hani-nabil)
- **Email:** nabil.hani@polytech-lille.net · nabil04hani@gmail.com

All code and documentation in this repository are released under the [MIT License](LICENSE). You are free to explore, reuse, and adapt the material with proper attribution.
