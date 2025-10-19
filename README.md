# 🎓 Nabil Hani – Engineering Academic Portfolio (Polytech Lille 2024‑2027)
🌐 **Live Portfolio Website:** [nabilhani.dev](file:///C:/Users/nabil/OneDrive/Documents/GitHub/Academic-Portfolio/CV_Website/index.html)
<div align="center">
<img src="./assets/polytech2022.png" alt="Polytech Lille Logo" width="360" />
  <br/><br/>
  <em>“From algorithmic proofs to interactive dashboards, this repository gathers the projects that shaped my engineering journey at Polytech Lille.”</em>
  <br/><br/>
  <img src="https://img.shields.io/badge/Low%20Level-C%20%26%20Algorithms-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Algorithms Badge" />
  <img src="https://img.shields.io/badge/Object%20Oriented-Java%20%26%20Swing-E76F00?style=for-the-badge&logo=java&logoColor=white" alt="Java Swing Badge" />
  <img src="https://img.shields.io/badge/Web-HTML5%20%7C%20CSS3%20%7C%20JS-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="Web Badge" />
  <img src="https://img.shields.io/badge/Data-BI%20Dashboards-4B8BBE?style=for-the-badge&logo=plotly&logoColor=white" alt="Data Badge" />
  <br/><br/>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" alt="C++" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/java/java-original.svg" alt="Java" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/javascript/javascript-original.svg" alt="JavaScript" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/html5/html5-original.svg" alt="HTML5" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/css3/css3-original.svg" alt="CSS3" height="50" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/mysql/mysql-original.svg" alt="SQL" height="50" />
</div>

Every directory is a self-contained deliverable that mixes coursework requirements with personal enhancements. The documentation below walks through each project, explains its architecture, highlights representative files, and gives you everything needed to compile, run, or explore the artefacts.

---

## 🗺️ Quick Navigation
- [✨ Portfolio Snapshot](#-portfolio-snapshot)
- [🧠 Algorithms & Systems Projects](#-algorithms--systems-projects)
  - [Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)](#dinic-maximum-flow-solver-projet_sd_graphes)
  - [Penté Strategy Game Toolkit (`Penté/`)](#penté-strategy-game-toolkit-penté)
- [🎮 Object-Oriented Games in Java](#-object-oriented-games-in-java)
  - [Complete Minesweeper Engine & GUI (`Demineur/`)](#complete-minesweeper-engine--gui-demineur)
  - [Packaged Minesweeper Build (`Demineur_2/`)](#packaged-minesweeper-build-demineur_2)
- [🌐 Web Engineering Projects](#-web-engineering-projects)
  - [Interactive CV Website (`CV_Website/`)](#interactive-cv-website-cv_website)
  - [BI/Data Dashboard Prototype (`Projet_Data/`)](#bidata-dashboard-prototype-projet_data)
  - [Flood It Web Game (`Web-Dev-Flood-It/`)](#flood-it-web-game-web-dev-flood-it)
- [📬 Contact & License](#-contact--license)

---
## 🧠 Algorithms & Systems Projects

## ✨ Portfolio Snapshot

| Track | Core Themes | Signature Artefacts |
| :--- | :--- | :--- |
| **Algorithms & Systems** | Residual networks, pointer-rich data structures, Unix workflows | Dinic solver in C with bespoke adjacency lists; CLI toolkit for Penté captures |
| **Object-Oriented Design** | MVC separation, exception-driven control flow, Swing UI | Minesweeper engine + GUI, reusable cell hierarchy, compiled demo build |
| **Web Engineering** | Responsive layouts, Bootstrap components, client-side rendering | CV microsite with Chart.js widgets, interactive dashboard fed by CSV data |
| **Data & Storytelling** | KPI logic, data cleaning, visual grammar | Plotly charts, fluid-meter gauges, scripted aggregations for socio-economic indicators |

> **Tip:** Each project folder contains its own assets (source files, datasets, PDFs). Browse them directly if you want a deeper dive into the implementation.

**Architecture layers**
- **Parsing & graph construction** — `Projet.c`, `graphe.h`, `sommet.h`, `arc.h`  
  `buildGraph` consumes DIMACS streams, instantiates vertices, and injects arcs via `ajouterArc`. Each `Arc` tracks capacity, flow, successor, and the reverse pointer.
- **Residual network builder** — `buildRG`  
  Clones the base graph into a residual representation with paired forward/backward arcs and **O(1) updates** through `reverse` links.
- **Augmenting path search** — `chemin.h`, `shortestPath`  
  BFS produces level graphs and returns a `Chemin` structure listing predecessors so augmentation can replay the route.
- **Flow augmentation** — `minCapa`, `updateFlowInRG`, `updateFlowInNet`  
  Computes the bottleneck (`minCapa`), adjusts residual capacities, then syncs flows back to the master graph.
- **Reporting** — `afficherFlots`, `ecrireResultatDansFichier`  
  Prints saturated arcs and writes a summary file with the max-flow value and per-arc distribution.

## 🧠 Algorithms & Systems Projects

### Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)
**Tech stack:** ISO C99, custom pointer-based structures, `gcc`, `Makefile`, DIMACS network format

> Implements Dinic's algorithm end to end: parsing, residual network construction, BFS layer building, augmentation, and result export.

**Highlights**
- Residual network representation with paired arcs and `reverse` pointers for **O(1)** capacity updates.
- BFS-based level graph stored as a `Chemin` structure to replay augmenting paths cleanly.
- Report generator that logs maximum flow values and per-arc usage to user-defined output files.

**Key files**
- `Projet.c` — orchestrates parsing, residual graph construction, augmenting path search, and result export.
- `graphe.h`, `sommet.h`, `arc.h`, `chemin.h` — modular headers for graph primitives and path bookkeeping.
- `Makefile` — reproducible build script with `make`, `make clean`, and dependency tracking.
- `ReadMe.txt` — original (French) user guide explaining benchmarks and DIMACS usage.

**Run it yourself**
```bash
cd Projet_SD_Graphes
make                        # builds the Projet executable
./Projet resultats_net1.txt < net1.txt
./Projet resultats_G_2500.txt < G_2500_7500.max
```
The solver streams DIMACS input from `stdin`, writes a detailed flow report to the file specified as the first argument, and echoes progress to the console.

**Takeaways**
- Manual memory management for adjacency lists reinforced safe pointer ownership patterns.
- Reverse-arc pointers kept augmentations fast, yielding strong performance even on large stress tests.
- Project grade: **16/20**, validated against both hand-checked and large synthetic networks.

Utilities to validate sequences and count forced captures.

### Penté Strategy Game Toolkit (`Penté/`)
**Tech stack:** ANSI C, 19×19 boards, console interaction, PDF documentation

> A command-line coach for Penté (five-in-a-row with capture mechanics) supporting full gameplay, capture detection, and training scenarios.

**Highlights**
- ASCII-rendered 19×19 board with coordinate labels and live capture counts.
- Capture detection scans all eight directions per move, mirroring official Penté rules.
- Modular routines ready for AI experimentation or heuristic extensions.

**Key files**
- `pente.c` — single-file engine with `init_jeu`, `afficher_plateau`, `verif_captures`, `verif_alignement`, and `tour_joueur`.
- `pente` — bundled executable for immediate play on Linux.
- `pente1.txt` … `pente7.txt` — curated starting positions for tactical analysis.
- `Algorithmique et Programmation - Rapport.pdf` — 25-page (French) report detailing strategy and complexity findings.

**Usage**
```bash
cd Penté
./pente                  # use the bundled binary
# or rebuild from source
gcc -Wall -O2 -o pente pente.c
./pente
```
During gameplay the program redraws the board after every move, tracks capture totals, and declares a win on either five-in-a-row or capture thresholds.

**Takeaways**
- Robust input validation prevents illegal coordinates or double placements.
- Capture logic supports simultaneous multi-direction captures.
- Provides a solid base for adding AI opponents or pattern-analysis tooling.

---

## 🎮 Object-Oriented Games in Java

### Complete Minesweeper Engine & GUI (`Demineur/`)
**Tech stack:** Java 17+, Swing, custom exception hierarchy, MVC architecture

> A full Minesweeper clone separating rule enforcement, UI rendering, and error propagation for clarity and testability.

**Highlights**
- Lazy bomb placement after the first click guarantees safe openings (`placerBombes`).
- Recursive flood fill (`propagationRecursive`) exposes contiguous empty regions without revisiting cells.
- Exception-driven flow (`GameLostException`, `GameWonException`) decouples engine logic from the Swing UI.

**Package overview**
- `lib/` — core engine (`Demineur`, `AbstractCell`, `StandardCell`, `BombCell`).
- `exceptions/` — domain-specific exceptions for invalid moves and end-game states.
- `gui/` — Swing front end with `DemineurUI`, `SetupDialog`, `GamePanel`, and `TopPanel`.

**Build & launch**
```bash
cd Demineur
javac exceptions/*.java gui/*.java lib/*.java
java gui.DemineurUI
```
The Swing window adapts to any board size you configure and keeps timers and bomb counters in sync as you flag cells.

**Takeaways**
- UI initialisation occurs on the Event Dispatch Thread via `SwingUtilities.invokeLater`.
- Clear separation of concerns makes it easy to test engine logic headlessly.
- Ready for enhancements such as high-score tracking or theme switching.

Controller: Mouse events, flagging/chording, game state transitions.

### Packaged Minesweeper Build (`Demineur_2/`)
**Tech stack:** Java 17+, identical source tree with bundled `.class` artefacts

> A ready-to-run distribution of the Minesweeper project, perfect for demonstrations when a compiler is unavailable.

**Highlights**
- Mirrors the `Demineur/` packages (`gui/`, `lib/`, `exceptions/`) with both sources and compiled classes.
- Launches instantly using the packaged bytecode; simply recompile if you tweak the sources.
- Serves as a baseline for benchmarking UI experiments without touching the original build.

**Quick start**
```bash
cd Demineur_2
java gui.DemineurUI        # uses the bundled .class files
# rebuild after editing source code
javac exceptions/*.java gui/*.java lib/*.java
```

---

## 🌐 Web Engineering Projects

### Interactive CV Website (`CV_Website/`)
**Stack:** HTML5, CSS3, Bootstrap 5, vanilla JavaScript, Chart.js

> A multi-page résumé experience combining polished styling with dynamic widgets (skills doughnut chart, interactive CV injection, lightweight mini-game).

**Highlights**
- `index.html` landing page with hero banner, call-to-action buttons, and smooth-scrolling navigation.
- Supporting pages (`cv.html`, `liens.html`, `loisirs.html`) reuse the shared stylesheet for consistent branding.
- `styles.css` layers gradients, custom typography, and card styling on top of Bootstrap.
- `scripts.js` injects structured CV data, renders Chart.js visuals, and powers a DOM-based clicker mini-game.

**Preview**
Open `CV_Website/index.html` in any modern browser. For best results, serve the directory with a lightweight static server (e.g., `npx serve`) to mimic production hosting and ensure relative assets resolve correctly.

---

### BI/Data Dashboard Prototype (`Projet_Data/`)
**Stack:** HTML5, CSS3, vanilla JavaScript, PapaParse, Plotly.js, SVG iconography

> A client-side data storytelling experiment built around INSEE socio-economic datasets. Upload two CSV files (Métropole + Réunion) to unlock interactive charts and KPI gauges.

**Highlights**
- `index.html` introduces the workflow and requests the required CSV datasets.
- `analyse.html` renders Plotly charts covering household composition, age brackets, and housing evolution.
- `indicateurs.html` showcases KPI cards and animated gauges powered by `js-fluid-meter.js`.
- `script.js` validates uploads, parses data with PapaParse, aggregates metrics, and hydrates the dashboard dynamically.

**Try it out**
```bash
cd Projet_Data
python3 -m http.server 8000   # or any static server
# visit http://localhost:8000 in your browser
```
Upload `carreaux_nivNaturel_met.csv` and `carreaux_nivNaturel_reun.csv` when prompted to animate charts, KPI cards, and commentary based on the loaded figures.

Bash

### Flood It Web Game (`Web-Dev-Flood-It/`)
**Stack:** HTML5, CSS3, vanilla JavaScript

> A browser implementation of the classic Flood It puzzle with configurable grid sizes, colour palettes, and challenge mode.

**Highlights**
- Recursive flood-fill algorithm (`remplir`) propagates colour changes through adjacent tiles.
- Dynamic grid generator builds the board and palette based on user-selected options.
- Challenge mode imposes move limits and tracks performance for replay value.

**Preview**
Open `Web-Dev-Flood-It/index.html` directly in a browser, or serve the directory via a static server for local development.

Chart.js widgets for skill visualisation.

Mobile-first layout with smooth scrolling.

Preview locally

Bash

cd CV_Website
# open index.html in your browser (no server required)
BI/Data Dashboard Prototype (Projet_Data/)
Data exploration dashboards (Plotly/JS) driven by CSV/JSON data.

Features

KPIs and cards, trend charts, and categorical breakdowns.

Simple data cleaning & aggregation scripts.

Fluid-meter/indicator visuals for at-a-glance status.

Run

Bash

cd Projet_Data
# open index.html (uses client-side Plotly)
Flood It Web Game (Web-Dev-Flood-It/)
A front-end implementation of the classic puzzle game, Flood It, using core web technologies.

Highlights

Recursive Flood Fill: Used a recursive function (remplir) to implement the core game mechanic of propagating the selected color to adjacent cells of the same color.

DOM Manipulation: Dynamic generation of the game grid and color palette based on user configuration inputs.

Game Modes: Includes a Challenge Mode with move limits.

Preview locally

## 📬 Contact & License

- **LinkedIn:** [linkedin.com/in/hani-nabil](https://www.linkedin.com/in/hani-nabil)
- **Email:** nabil.hani@polytech-lille.net · nabil04hani@gmail.com

All material in this repository is released under the [MIT License](LICENSE). Feel free to explore, reuse, and adapt with attribution — and don’t hesitate to reach out if a project catches your interest!
