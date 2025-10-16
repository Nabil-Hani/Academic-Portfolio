document.getElementById('btn-fr').addEventListener('click', function () {
    let cvContent = document.getElementById('cv-content');
    cvContent.innerHTML = `
        <h2>Formation</h2>
        <p>Cycle ingénieur en Informatique et Statistique - Polytech Lille</p>

        <h2>Expérience</h2>
        <p>Stage chez IBM - Développement backend</p>

        <h2>Compétences</h2>
        <div class="progress mb-2">
            <div class="progress-bar bg-success" role="progressbar" style="width: 90%">HTML, CSS, JavaScript - 90%</div>
        </div>
        <div class="progress mb-2">
            <div class="progress-bar bg-info" role="progressbar" style="width: 80%">Bootstrap, React - 80%</div>
        </div>
        <div class="progress mb-2">
            <div class="progress-bar bg-warning" role="progressbar" style="width: 85%">C, C++, Python - 85%</div>
        </div>
        <div class="progress mb-4">
            <div class="progress-bar bg-danger" role="progressbar" style="width: 75%">SQL, XML, JSON - 75%</div>
        </div>

        <h2>Graphique des Compétences</h2>
        <canvas id="skillsChart" width="400" height="200"></canvas>

        <h2>Loisirs</h2>
        <p>Football, Musique</p>

        <button class="btn btn-primary mt-3" onclick="startGame()">🎯 Jouer à un mini-jeu !</button>
        <div id="game-container" class="mt-3"></div>
    `;

    createChart();
});

function createChart() {
    const ctx = document.getElementById('skillsChart').getContext('2d');
    new Chart(ctx, {
        type: 'doughnut',
        data: {
            labels: ['HTML/CSS/JS', 'Bootstrap/React', 'C/C++/Python', 'SQL/XML/JSON'],
            datasets: [{
                data: [90, 80, 85, 75],
                backgroundColor: ['#28a745', '#17a2b8', '#ffc107', '#dc3545']
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false
        }
    });
}

function startGame() {
    const gameContainer = document.getElementById('game-container');
    let score = 0;
    gameContainer.innerHTML = `<p>Score: <span id="score">0</span></p><button class="btn btn-success" onclick="increaseScore()">Cliquez-moi !</button>`;
}

function increaseScore() {
    let scoreElement = document.getElementById('score');
    let currentScore = parseInt(scoreElement.textContent);
    scoreElement.textContent = currentScore + 1;
}

