
// Our puzzle collection
const puzzles = [
    {
        emojis: ["🦁", "👑", "🌅"],
        answer: "the lion king",
        hint: "A young lion becomes king"
    },
    {
        emojis: ["🕷️", "👨", "🏙️"],
        answer: "spiderman",
        hint: "A superhero who climbs buildings"
    },
    {
        emojis: ["🚢", "🧊", "💔"],
        answer: "titanic",
        hint: "A famous ship disaster"
    },
    {
        emojis: ["🍔", "👑", "🍟"],
        answer: "burger king",
        hint: "A popular fast food chain"
    }
];

// Game variables
let currentPuzzle;
let revealedEmojis;
let score = 0;
let streak = 0;
let attempts = 5;

// Select a random puzzle
function startGame() {
    const randomIndex = Math.floor(Math.random() * puzzles.length);

    currentPuzzle = puzzles[randomIndex];
    revealedEmojis = 1;
    attempts = 5;

    displayEmojis();

    document.getElementById("message").textContent = "";
    document.getElementById("answer-input").value = "";
}

// Display the currently revealed emojis
function displayEmojis() {
    const display = document.getElementById("emoji-display");

    display.textContent = currentPuzzle.emojis
        .slice(0, revealedEmojis)
        .join(" ");
}

// Check the player's answer
function checkAnswer() {
    const input = document.getElementById("answer-input");
    const guess = input.value.trim().toLowerCase();

    if (guess === "") {
        document.getElementById("message").textContent =
            "Enter an answer first!";
        return;
    }

    if (guess === currentPuzzle.answer) {
        score += 10;
        streak++;

        document.getElementById("message").textContent =
            "Correct! 🎉 +10 points!";

        updateStats();

        setTimeout(startGame, 1500);
    } else {
        attempts--;
        streak = 0;

        if (revealedEmojis < currentPuzzle.emojis.length) {
            revealedEmojis++;
            displayEmojis();
        }

        if (attempts === 0) {
            document.getElementById("message").textContent =
                "Game over! Answer: " + currentPuzzle.answer;

            setTimeout(startGame, 2500);
        } else {
            document.getElementById("message").textContent =
                "Incorrect! Attempts left: " + attempts;
        }

        updateStats();
    }

    input.value = "";
}

// Update score and streak
function updateStats() {
    document.getElementById("score").textContent = score;
    document.getElementById("streak").textContent = streak;
}

// Connect the button to the game
document.getElementById("submit-button").addEventListener("click", checkAnswer);

// Start the first puzzle
startGame();
