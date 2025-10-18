# 🎓 Nabil Hani – Engineering Academic Portfolio (Polytech Lille 2024‑2027)

<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/fr/thumb/4/45/Logo_Polytech_Lille.svg/512px-Logo_Polytech_Lille.svg.png" alt="Polytech Lille Logo" width="180" />
  
  <blockquote><em>"From algorithmic proofs to interactive dashboards, this repository gathers the projects that shaped my engineering journey at Polytech Lille."</em></blockquote>
  
  <img src="https://img.shields.io/badge/Low%20Level-C%20%26%20Algorithms-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Algorithms Badge" />
  <img src="https://img.shields.io/badge/Object%20Oriented-Java%20%26%20Swing-E76F00?style=for-the-badge&logo=java&logoColor=white" alt="Java Swing Badge" />
  <img src="https://img.shields.io/badge/Web-HTML5%20%7C%20CSS3%20%7C%20JS-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="Web Badge" />
  <img src="https://img.shields.io/badge/Data-BI%20Dashboards-4B8BBE?style=for-the-badge&logo=plotly&logoColor=white" alt="Data Badge" />
</div>

<p align="center">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" alt="C++" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/java/java-original.svg" alt="Java" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/javascript/javascript-original.svg" alt="JavaScript" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/html5/html5-original.svg" alt="HTML5" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/css3/css3-original.svg" alt="CSS3" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/mysql/mysql-original.svg" alt="SQL" height="50" />
</p>

Every directory is a self-contained deliverable that mixes coursework requirements with personal enhancements. The documentation below walks through each project, explains its architecture, highlights representative files, and gives you everything needed to compile, run, or explore the artefacts.

---

## 🗺️ Quick Navigation
- [✨ Portfolio Snapshot](#-portfolio-snapshot)
- [🧠 Algorithms & Systems Projects](#-algorithms--systems-projects)
  - [Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)](#dinic-maximum-flow-solver-projet_sd_graphes)
  - [Penté Strategy Game Toolkit (`Penté/`)](#pente-strategy-game-toolkit-penté)
- [🎮 Object-Oriented Games in Java](#-object-oriented-games-in-java)
  - [Complete Minesweeper Engine & GUI (`Demineur/`)](#complete-minesweeper-engine--gui-demineur)
  - [Packaged Minesweeper Build (`Demineur_2/`)](#packaged-minesweeper-build-demineur_2)
- [🌐 Web Engineering Projects](#-web-engineering-projects)
  - [Interactive CV Website (`CV_Website/`)](#interactive-cv-website-cv_website)
  - [BI/Data Dashboard Prototype (`Projet_Data/`)](#bidata-dashboard-prototype-projet_data)
- [📬 Contact & License](#-contact--license)

---

## ✨ Portfolio Snapshot

| Track | Core Themes | Signature Artefacts |
| :--- | :--- | :--- |
| **Algorithms & Systems** | Residual networks, pointer-rich data structures, Unix workflows | Dinic solver in C with bespoke adjacency lists; CLI toolkit for Penté captures |
| **Object-Oriented Design** | MVC separation, exception-driven control flow, Swing UI | Minesweeper engine + GUI, reusable cell hierarchy, compiled demo build |
| **Web Engineering** | Responsive layouts, Bootstrap components, client-side rendering | CV microsite with Chart.js widgets, interactive dashboard fed by CSV data |
| **Data & Storytelling** | KPI logic, data cleaning, visual grammar | Plotly charts, fluid meter gauges, scripted aggregations for socio-economic indicators |

> **Tip:** Each project folder contains its own assets (source files, datasets, PDFs). Browse them directly if you want a deeper dive into the implementation.

---

## 🧠 Algorithms & Systems Projects

### Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)
**Tech stack:** ISO C99, custom pointer-based structures, `gcc`, `Makefile`, DIMACS network format

> Implements Dinic's algorithm end to end: parsing, residual network construction, BFS layer building, augmentation, and result export.

**Architecture layers**
- **Parsing & graph construction (`Projet.c`, `graphe.h`, `sommet.h`, `arc.h`):** `buildGraph` consumes DIMACS streams, instantiates vertices, and injects arcs via `ajouterArc`. Each `Arc` tracks capacity, flow, successor, and the reverse pointer.
- **Residual network builder (`buildRG`):** Clones the base graph into a residual representation with paired forward/backward arcs and $O(1)$ updates through the `reverse` links.
- **Augmenting path search (`chemin.h`, `shortestPath`):** BFS produces level graphs and returns a `Chemin` structure listing predecessors so the augmentation phase can replay the route.
- **Flow augmentation (`minCapa`, `updateFlowInRG`, `updateFlowInNet`):** Determines the bottleneck, adjusts residual capacities, and synchronises flows back to the master graph before looping.
- **Reporting (`afficherFlots`, `ecrireResultatDansFichier`):** Prints all saturated arcs and writes a summary file with the max-flow value and per-arc flow distribution.

**Key deliverables**
- `Makefile` — portable build script with `make`, `make clean`, and dependency tracking.
- `ReadMe.txt` — original (French) usage guide and benchmark commentary.
- Test networks (`net1.txt`, `net2.txt`, `G_100_300.max`, `G_2500_7500.max`, …) — cover both pedagogical and stress-test scenarios.

**Run it yourself**
```bash
cd Projet_SD_Graphes
make                        # builds the Projet executable
./Projet resultats_net1.txt < net1.txt
./Projet resultats_G_2500.txt < G_2500_7500.max
```
The solver streams DIMACS input from `stdin`, writes the detailed flow report to the file given as the first argument, and echoes intermediate progress to the console.

**Highlights & learnings**
- Manual memory management (allocation/free) for adjacency lists reinforced safe pointer handling.
- Reverse-arc pointers turned capacity updates into constant-time operations, keeping the overall complexity at $O(V^2E)$ in the worst case but efficient in practice.
- The project earned **16/20**, validated by manual flow calculations and large synthetic graphs.

---

### Penté Strategy Game Toolkit (`Penté/`)
**Tech stack:** ANSI C, 19×19 grids, console interaction, PDF report

> A command-line coach for Penté (five-in-a-row with capture mechanics) supporting full gameplay, capture detection, and training scenarios.

**Code map**
- `pente.c` — single-file engine featuring:
  - `init_jeu` to reset the 19×19 board and score counters.
  - `afficher_plateau` for ASCII rendering with axis labels.
  - `verif_captures` to evaluate eight directions after each move, remove captured pairs, and update `scoreX`/`scoreO`.
  - `verif_alignement` to detect winning sequences of five aligned stones.
  - `tour_joueur` to validate input coordinates, apply moves, toggle turns, and exit on victory or resignation.
- `pente` — precompiled executable (Linux) for instant play.
- `pente1.txt` … `pente7.txt` — curated positions used for tactical analysis and evaluation.
- `Algorithmique et Programmation - Rapport.pdf` — 25-page report discussing heuristics, complexity, and strategic insights (French).

**Usage**
```bash
cd Penté
./pente                  # play using the bundled binary
# or rebuild from source
gcc -Wall -O2 -o pente pente.c
./pente
```
During gameplay the program prints board state after each move, tracks capture counts, and announces the winner when an alignment or the capture threshold is reached.

**What to look for**
- Robust input validation prevents illegal coordinates and double-occupancy moves.
- Capture logic mirrors official Penté rules, including simultaneous multi-direction captures.
- Great starter for experimenting with heuristic evaluation or AI opponents by extending the move loop.

---

## 🎮 Object-Oriented Games in Java

### Complete Minesweeper Engine & GUI (`Demineur/`)
**Tech stack:** Java 17+, Swing, custom exception hierarchy, MVC architecture

> A full Minesweeper clone separating rule enforcement, UI rendering, and error propagation for clarity and testability.

**Package overview**
- `lib/`
  - `Demineur` orchestrates the game grid, lazy bomb placement (`placerBombes` occurs after the first click), recursive propagation (`propagationRecursive`), flag handling, and victory checks.
  - `AbstractCell`, `StandardCell`, `BombCell` encapsulate state transitions (revealed, flagged, adjacent bomb counts) and expose a consistent API to the UI layer.
- `exceptions/`
  - `InvalidMoveException`, `GameLostException`, `GameWonException` signal engine outcomes without coupling to Swing components.
- `gui/`
  - `DemineurUI` bootstraps the app, listens to mouse events, and reacts to engine signals.
  - `SetupDialog` collects grid dimensions and mine counts before instantiating a game.
  - `GamePanel` renders the clickable grid with double-buffered painting.
  - `TopPanel` displays timers, mine counters, and status messages.

**Gameplay flow**
1. `SetupDialog` gathers difficulty parameters and instantiates `Demineur`.
2. First click triggers `placerBombes`, guaranteeing a safe start.
3. UI events call engine methods; exceptions bubble back to toggle messages or end the session.
4. A win/loss dialog appears, and the player can immediately start a new configuration.

**Build & launch**
```bash
cd Demineur
javac exceptions/*.java gui/*.java lib/*.java
java gui.DemineurUI
```
The Swing window adapts to the board size you choose and keeps bomb counters in sync as you flag cells.

**Notable details**
- Event dispatch thread (EDT) considerations handled by invoking the UI inside `SwingUtilities.invokeLater`.
- Recursive clearing prevents revisiting cells thanks to guard clauses, avoiding stack overflows even on large boards.
- Exceptions replace boolean return codes, improving readability and decoupling layers.

---

### Packaged Minesweeper Build (`Demineur_2/`)
**Tech stack:** Java 17+, identical source tree + compiled `.class` artefacts

> A ready-to-run packaging of the Minesweeper project, useful for demonstrations or grading when compilation time is limited.

**What’s inside**
- Mirror of the `Demineur/` directory structure (`gui/`, `lib/`, `exceptions/`) with both `.java` and `.class` files.
- Precompiled bytecode allows launching the game immediately with the standard Java runtime.
- Source code remains editable; re-running `javac` refreshes the corresponding `.class` files.

**Quick start**
```bash
cd Demineur_2
java gui.DemineurUI        # uses the bundled .class files
# rebuild if you change the sources
javac exceptions/*.java gui/*.java lib/*.java
```
This folder doubles as a baseline for benchmarking UI tweaks against the canonical solution in `Demineur/`.

---

## 🌐 Web Engineering Projects

### Interactive CV Website (`CV_Website/`)
**Stack:** HTML5, CSS3, Bootstrap 5, vanilla JavaScript, Chart.js

> A multi-page résumé website combining polished styling with dynamic widgets (skill chart, interactive CV injection, lightweight mini-game).

**Structure**
- Pages: `index.html` (landing page with hero banner and call-to-action buttons), `cv.html`, `liens.html`, `loisirs.html`.
- Styling: `styles.css` layers custom typography, gradients, and component spacing on top of Bootstrap defaults.
- Behaviour: `scripts.js` listens for language buttons, injects CV content, renders a doughnut chart via Chart.js, and spawns a clicker mini-game.
- Assets: `/assets/` stores imagery used throughout the site (profile photo, icons).

**Highlights**
- Responsive navbar with smooth scrolling, collapsible sections, and clear CTA buttons.
- Progress bars and Chart.js visual convey skill distribution interactively.
- The embedded mini-game showcases DOM manipulation and state updates in real time.

**Preview**
Simply open `CV_Website/index.html` in any modern browser. For best results, serve the directory with a static server (e.g., `npx serve`) to mimic production hosting and ensure relative asset paths resolve correctly.

---

### BI/Data Dashboard Prototype (`Projet_Data/`)
**Stack:** HTML5, CSS3, vanilla JavaScript, PapaParse, Plotly.js, SVG iconography

> A client-side data storytelling experiment built around INSEE socio-economic datasets. Upload two CSV files (Métropole + Réunion) to unlock interactive charts and KPI gauges.

**Front-end layout**
- `index.html` — onboarding page describing the dataset requirements and providing upload controls.
- `analyse.html` — hosts Plotly charts (household composition, age distribution, housing evolution).
- `indicateurs.html` — presents KPI cards, animated gauges driven by `js-fluid-meter.js`, and narrative insights.
- `style.css` — cohesive dark-themed UI with responsive cards and chart containers.

**Data pipeline (`script.js`)**
1. `traitement()` validates file selection and leverages PapaParse to read both CSVs asynchronously.
2. `genererGraphiques()` aggregates metrics, producing:
   - Dual pie charts for household composition (`chart1`).
   - Comparative bar chart for age brackets (`chart2`).
   - Line chart showing housing stock evolution (`chart3`).
   - Additional helpers compute poverty indicators, household size distributions, and populate KPI gauges.
3. Parsed data triggers DOM updates that reveal hidden dashboard sections once processing completes.

**Try it out**
```bash
cd Projet_Data
python3 -m http.server 8000   # or any static server
# open http://localhost:8000 in your browser
```
Upload `carreaux_nivNaturel_met.csv` and `carreaux_nivNaturel_reun.csv` when prompted. The dashboard will animate charts, update KPI cards, and display commentary tied to the loaded figures.

**Extras**
- `img/` folder with pictograms (income, poverty, demographics) used throughout the narrative.
- Detailed inline comments (French) explaining every aggregation step — ideal for academic review or future refactoring into a modular JS architecture.

---

## 📬 Contact & License

- **LinkedIn:** [linkedin.com/in/hani-nabil](https://www.linkedin.com/in/hani-nabil)
- **Email:** nabil.hani@polytech-lille.net · nabil04hani@gmail.com

All material in this repository is released under the [MIT License](LICENSE). Feel free to explore, reuse, and adapt with attribution — and don’t hesitate to reach out if a project catches your interest!
