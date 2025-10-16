# 🎓 Nabil Hani: Engineering Academic Portfolio (Polytech Lille 2024-2025)

<p align="center">
  <img src="https://img.shields.io/badge/Polytech_Lille-IS3-blue?style=for-the-badge" alt="Polytech Lille Badge">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Badge">
  <img src="https://img.shields.io/badge/SQL-4479A1?style=for-the-badge&logo=postgresql&logoColor=white" alt="SQL Badge">
  <img src="https://img.shields.io/badge/Web_Development-HTML_CSS_JS-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="Web Dev Badge">
</p>

Welcome! I am an Engineering Student specializing in **Core Computing (C/C++)** and **Data Analysis** at Polytech Lille (Class of 2026). This portfolio showcases my hands-on application of complex algorithms, efficient data structures, and fundamental software engineering principles.

My focus is on robust, system-level programming and leveraging data fundamentals to solve challenging problems.

---

## 🛠️ Core Technical Expertise

| Domain | Key Technologies & Concepts |
| :--- | :--- |
| **Low-Level & Algorithms** | **C** (Mastery), Data Structures (Lists, Queues), **Dynamic Memory Allocation** (`malloc`/`free`), Unix System Calls, `Makefiles`. |
| **Databases & BI** | **SQL** (Queries & Schema Design), Data Aggregation, KPI Logic, Conceptual experience with Qlik Sense. |
| **Web Development** | **HTML5**, **CSS3**, **JavaScript (DOM Manipulation)**, Responsive Design (Bootstrap). |
| **Core Engineering** | **C++**, **Java** (OOP Fundamentals), Algorithmic Complexity ($O(n+m)$ analysis), Problem Solving. |

---

## 🚀 Featured Academic Projects

This curated selection of projects highlights my ability to transition from theoretical analysis to rigorous, working code. All source code and detailed reports are available in the corresponding folders within this repository.

| Project Title | Core Technology | Key Skills Demonstrated | Link to Project |
| :--- | :--- | :--- | :--- |
| **Dinic Algorithm for Max Flow** | **C**, Graphes & Combinatoires | Advanced Algorithm Implementation, Custom Linked List Structures, Time/Space Complexity Analysis, Graph Residual Modeling. | [View Project Folder](Graphes-Combinatoires-DINIC/) |
| **'Flood It' Web Game** | **HTML, CSS, JavaScript** | Front-end Game Logic, DOM Manipulation, Recursive Flood Fill Algorithm, Responsive UI Design (Bootstrap). | [View Project Folder](Web-Dev-Flood-It/) |
| **Business Intelligence Intern** | BI/Data Aggregation, SQL | KPI Development, Data Visualization (Qlik Sense), Teamwork, Adaptability. | *(Experience Only - See LinkedIn)* |

---

## 📜 Project Deep Dive: Dinic Algorithm Implementation

This was a major project combining structures and algorithms, resulting in a robust implementation with a final grade of **16/20**.

### 🎯 Goal
To study, analyze, and implement the high-performance **DINIC Algorithm** in **C** for calculating the maximum flow in a network.

### 💡 Core Design Choices
The project required a detailed analysis of data structures [cite: 210, 684][cite_start], leading to the final choice: a **Linked List of Successors** with **Pointers to Reverse Arcs**.

| Structure Chosen | Justification | Complexity |
| :--- | :--- | :--- |
| **Linked List of Successors** | [cite_start]Optimal memory usage [cite: 303] (proportional to arcs) [cite_start][cite: 243][cite_start], fast access to successors ($O(d^+(s))$) [cite: 258][cite_start], and excellent flexibility for dynamic addition/deletion of arcs[cite: 284]. | [cite_start]$O(n+m)$ (Memory) [cite: 227] |
| **Pointers to Inverse Arcs** | [cite_start]Essential for modeling the **residual graph** (graphe d'écart)[cite: 295, 298]. [cite_start]This allows for fast, $O(1)$ update of capacities and flow reversals without searching the successor list[cite: 296, 299]. | [cite_start]$O(1)$ (Flow Update) [cite: 299] |

### 📈 Results & Validation
The program successfully calculated the maximum flow on complex test cases:

* **Réseau R1 (`net1.txt`):** Flot maximal **40** (Manual verification successful).
* **Réseau R2 (`net2.txt`):** Flot maximal **15** (Manual verification successful).
* **Large-Scale Test (`G_2500_7500.max`):** Successfully managed a graph with **2500 vertices and 7500 arcs**, confirming robustness and controlled memory consumption.

---

## 💻 Project Deep Dive: Flood It Game (Web Development)

This project focused on implementing game logic and front-end interaction using web technologies.

### 🎮 Goal
To develop a fully functional, browser-based version of the "Flood It" puzzle game, allowing users to customize grid size, color count, and play in a **Challenge Mode** with limited moves.

### 💡 Key Skills & Features

* **Recursive Flood Fill:** Used a recursive function (`remplir`) to implement the core game mechanic of propagating the selected color to adjacent cells of the same color.
* **DOM Manipulation:** Dynamic generation of the game grid and color palette based on user configuration inputs.
* **UI/UX:** Utilized **Bootstrap** for responsive layout and clean presentation, including a configuration page and an integrated tutorial.
* **Game State Management:** Tracking the number of moves and checking the victory/loss condition in real-time.

---

## 📬 Let's Connect

Currently actively seeking a **10-week minimum internship** in France (Lille preferred) or abroad between **April and August 2026**. I am eager to apply my skills in core development and technical analysis to a challenging industry role.

* 🔗 **www.linkedin.com/in/hani-nabil**
* 📧 **nabil.hani@polytech-lille.net** | **nabil04hani@gmail.com**
* 🏆 **Certifications:** C2 English Proficiency (CPE) and TOEIC (Score: 985/990).

---

## 📜 License

All code and documentation in this academic portfolio are licensed under the **MIT License**.

***
