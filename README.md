# 🎓 Nabil Hani – Engineering Academic Portfolio (Polytech Lille 2024‑2027)

Welcome to my consolidated portfolio. It gathers the course projects, personal exercises and reports I produced while studying computer engineering at **Polytech Lille**. Every folder in this repository contains a self‑contained project, from low‑level algorithmics in C to interactive web and Java applications.

---

## 🚀 At a Glance

| Domain | Technologies | Highlights |
| :--- | :--- | :--- |
| **Algorithms & Systems** | C, custom data structures, Unix tooling, Makefiles | Maximum flow solver with Dinic's algorithm, command line utilities for board games. |
| **Object Oriented Programming** | Java, Swing | Complete Minesweeper engine + GUI, exception‑driven gameplay flow. |
| **Web Engineering** | HTML5, CSS3, JavaScript, Bootstrap | Responsive résumé site, interactive data exploration dashboard. |
| **Data & BI** | SQL concepts, KPI design, data storytelling | Static prototype of BI dashboards built from INSEE open data. |

---

## 📂 Repository Map

- [`Projet_SD_Graphes/`](Projet_SD_Graphes/) – C implementation of Dinic's maximum flow algorithm with reusable graph primitives.
- [`Penté/`](Penté/) – C tools and datasets for analysing and playing the Penté (five‑in‑a‑row) strategy game.
- [`Demineur/`](Demineur/) – Java Minesweeper project structured around clean separation between model, view and controller layers.
- [`Demineur_2/`](Demineur_2/) – Alternate build of the Minesweeper engine packaged with compiled `.class` files.
- [`CV_Website/`](CV_Website/) – Multi‑page CV website showcasing professional experience and projects.
- [`Projet_Data/`](Projet_Data/) – Web dashboard mock-up for BI indicators, including interactive widgets powered by vanilla JS.

Each project directory includes its own source code, assets and—when relevant—compilation instructions or reports.

---

## 🔬 Systems & Algorithms Projects

### Dinic Maximum Flow Solver (`Projet_SD_Graphes/`)

*Language: C*

- Implements a reusable graph module (`graphe.h`, `sommet.h`, `arc.h`, `chemin.h`) supporting residual networks and adjacency lists with reverse-arc pointers.
- Core algorithm lives in `Projet.c` and is built with the provided `Makefile`.
- Sample datasets (`ReadMe.txt`) illustrate small and large flow networks to validate both correctness and performance.

**How to run**
```bash
cd Projet_SD_Graphes
make            # builds the executable with gcc
a.out < input   # run the solver against a graph description
```

### Penté Strategy Game Toolkit (`Penté/`)

*Language: C*

- Contains command-line utilities (`pente` executable, `pente.c`) for evaluating game states and trying move sequences.
- Bundled `.txt` files provide ready-to-use board configurations for testing heuristics.
- Includes a full project report (`Algorithmique et Programmation - Rapport.pdf`) describing the search strategy and complexity analysis.

---

## 🎮 Object-Oriented Games

### Minesweeper Engine & GUI (`Demineur/`)

*Language: Java*

- Core gameplay lives in the `lib/` package with an abstract cell hierarchy (`AbstractCell`, `StandardCell`, `BombCell`) and the `Demineur` controller.
- GUI classes in `gui/` (Swing) manage the setup dialog, grid rendering and user feedback.
- Custom exceptions in `exceptions/` keep the engine decoupled from the interface and simplify error handling.

**Compile & run**
```bash
cd Demineur
javac exceptions/*.java gui/*.java lib/*.java
java gui.DemineurUI
```

### Minesweeper Build with Binaries (`Demineur_2/`)

*Language: Java*

- Mirrors the structure of `Demineur/` and ships the compiled `.class` files for quick execution.
- Useful for demonstrations without needing to recompile; edit the `.java` sources for custom behaviour and rebuild if required.

---

## 🌐 Web & Data Experiences

### CV Website (`CV_Website/`)

*Stack: HTML, CSS, JavaScript, Bootstrap*

- Responsive multi-page personal site (`index.html`, `cv.html`, `loisirs.html`, `liens.html`).
- Custom styles (`styles.css`) complemented by Bootstrap for layout and typography.
- `scripts.js` adds interactive behaviours such as smooth scrolling and dynamic content toggles.

### Data Storytelling Dashboard (`Projet_Data/`)

*Stack: HTML, CSS, JavaScript*

- Prototype of a BI dashboard presenting socio-economic indicators with interactive charts and gauges.
- Pages (`index.html`, `analyse.html`, `indicateurs.html`) are styled by `style.css` and enhanced with `script.js` and `js-fluid-meter.js`.
- CSV datasets in the folder supply real figures to drive visualisations.

---

## 📬 Contact & Licensing

- **LinkedIn:** [linkedin.com/in/hani-nabil](https://www.linkedin.com/in/hani-nabil)
- **Email:** nabil.hani@polytech-lille.net / nabil04hani@gmail.com

All material in this repository is available under the [MIT License](LICENSE). Feel free to explore, reuse and adapt with attribution.
