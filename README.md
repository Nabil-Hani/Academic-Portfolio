# 🎓 Nabil Hani – Engineering Academic Portfolio (Polytech Lille 2024-2027)
<div align="center">
  <img src="[[https://upload.wikimedia.org/wikipedia/fr/thumb/4/45/Logo_Polytech_Lille.svg/512px-Logo_Polytech_Lille.svg.png](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.usinenouvelle.com%2Farticle%2Fpolytech-lille.N313913&psig=AOvVaw31408VbKi33XPP3GjvNjRL&ust=1760906912290000&source=images&cd=vfe&opi=89978449&ved=0CBUQjRxqFwoTCNjt88rPrpADFQAAAAAdAAAAABAL)](https://www.google.com/url?sa=i&url=https%3A%2F%2Fjmi.polytech-lille.fr%2F&psig=AOvVaw31408VbKi33XPP3GjvNjRL&ust=1760906912290000&source=images&cd=vfe&opi=89978449&ved=0CBUQjRxqFwoTCNjt88rPrpADFQAAAAAdAAAAABAW)" alt="Polytech Lille Logo" width="180" />
  <br/><br/>
  *“From algorithmic proofs to interactive dashboards, this repository gathers the projects that shaped my engineering journey at Polytech Lille.”*
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
## 📚 Table of Contents
1. [✨ Portfolio Snapshot](#-portfolio-snapshot)
2. [🧠 Algorithms & Systems Projects](#-algorithms--systems-projects)
   - [Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)](#dinic-maximum-flow-solver-projet_sd_graphes)
   - [Penté Strategy Game Toolkit (`Penté/`)](#penté-strategy-game-toolkit-penté)
3. [🎮 Object-Oriented Games in Java](#-object-oriented-games-in-java)
   - [Complete Minesweeper Engine & GUI (`Demineur/`)](#complete-minesweeper-engine--gui-demineur)
   - [Packaged Minesweeper Build (`Demineur_2/`)](#packaged-minesweeper-build-demineur_2)
4. [🌐 Web Engineering Projects](#-web-engineering-projects)
   - [Interactive CV Website (`CV_Website/`)](#interactive-cv-website-cv_website)
   - [BI/Data Dashboard Prototype (`Projet_Data/`)](#bidata-dashboard-prototype-projet_data)
   - [Flood It Web Game (`Web-Dev-Flood-It/`)](#flood-it-web-game-web-dev-flood-it)
5. [📬 Contact & License](#-contact--license)

---
## ✨ Portfolio Snapshot

| Track | Core Themes | Signature Artefacts |
| :--- | :--- | :--- |
| **Algorithms & Systems** | Residual networks, pointer-rich data structures, Unix workflows | Dinic solver in C with bespoke adjacency lists; CLI toolkit for Penté captures |
| **Object-Oriented Design** | MVC separation, exception-driven control flow, Swing UI | Minesweeper engine + GUI, reusable cell hierarchy, compiled demo build |
| **Web Engineering** | Responsive layouts, Bootstrap components, client-side rendering | CV microsite with Chart.js widgets, interactive dashboard fed by CSV data |
| **Data & Storytelling** | KPI logic, data cleaning, visual grammar | Plotly charts, fluid-meter gauges, scripted aggregations for socio-economic indicators |

> **Tip:** Each project folder contains its own assets (source files, datasets, PDFs). Browse them directly for a deeper dive into the implementation.

---
## 🧠 Algorithms & Systems Projects

### Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)
**Tech stack:** ISO C99, custom pointer-based structures, `gcc`, `Makefile`, DIMACS network format

Implements **Dinic’s algorithm** end-to-end: parsing, residual network construction, BFS level graph building, augmentation, and result export.

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

**Build & run**
```bash
cd Projet_SD_Graphes
make           # builds the solver using the Makefile
./Projet < data/sample.dimacs > out/result.txt
make clean     # remove build artefacts
Penté Strategy Game Toolkit (Penté/)
Command-line helpers for the board game Penté (capture rules, valid moves, simple heuristics).

Highlights

Board representation with fast capture detection.

Utilities to validate sequences and count forced captures.

Modular code to allow plugging different evaluation heuristics.

Run

Bash

cd Penté
# example run (adjust binary/args to your sources)
gcc -O2 -o pente src/*.c
./pente --size 19 --ai greedy
🎮 Object-Oriented Games in Java
Complete Minesweeper Engine & GUI (Demineur/)
A full Minesweeper implementation in Java with a clean MVC (Model-View-Controller) split.

What to look for

Model: Cell hierarchy (empty, numbered, mine), board generation, recursive flood-fill.

View: Swing components for board, status bar, timers, icons.

Controller: Mouse events, flagging/chording, game state transitions.

Quality: Exceptions for invalid states, unit-style tests for core rules.

Run

Bash

cd Demineur
javac -d out $(find src -name "*.java")
java -cp out com.nabilhani.demineur.Main
Packaged Minesweeper Build (Demineur_2/)
A trimmed, distributable variant of the Minesweeper app.

How to launch

Bash

cd Demineur_2
./gradlew run      # if Gradle wrapper is provided
# or:
java -jar build/demineur.jar
🌐 Web Engineering Projects
Interactive CV Website (CV_Website/)
Responsive personal CV website with Bootstrap and light client-side scripting.

Features

Sections for education, projects, and skills with iconography.

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

Bash

cd Web-Dev-Flood-It
# open index.html in your browser
📬 Contact & License
Contact
If you have questions, suggestions, or spot an issue, please open a GitHub issue in this repository.

License
This repository’s contents are intended for educational purposes. If a LICENSE file is present in a project subfolder, it supersedes this note for that sub-project.
