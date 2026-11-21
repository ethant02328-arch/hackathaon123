
const puzzles = [
    { emojis: ["🧑🏾‍🏫", "🏫", "🔬"], answer: "Skye", difficulty: "hard", hint: "Supplemental Instructor Hotspot (ebk)" },
    { emojis: ["⚙️", "🔧", "🏗️"], answer: "Bourns", difficulty: "medium", hint: "The lesser known CS building for engineers" },
    { emojis: ["💻", "🤖", "⚡"], answer: "Chung", difficulty: "medium", hint: "Heart attack for CS students" },
    { emojis: ["🪑", "👩‍🏫", "🧪"], answer: "Pierce", difficulty: "medium", hint: "Biologically substantial" },
    { emojis: ["📝", "🏛️", "🎓"], answer: "Olmsted", difficulty: "hard", hint: "Statistically speaking and pschologically demanding" },
    { emojis: ["📚", "🤫", "🔔"], answer: "Rivera", difficulty: "easy", hint: "The worst library" },
    { emojis: ["📚📚", "📚📚📚", "🌙"], answer: "Orbach", difficulty: "medium", hint: "The better library" },
    { emojis: ["🔭", "⚛️", "🧲"], answer: "Physics", difficulty: "easy", hint: "Legit in the name" },
    { emojis: ["🎤", "🪑", "👥"], answer: "Lecture Hall", difficulty: "medium", hint: "Most of the classes are here honestly big ting" },
    { emojis: ["🧑‍🏫", "📖", "🏢"], answer: "UTLF", difficulty: "hard", hint: "The one building that never shows up on maps" },
    { emojis: ["🧬", "🔬", "🧫"], answer: "Genomics", difficulty: "medium", hint: "Jeans" },
    { emojis: ["💼", "📈", "💰"], answer: "Business", difficulty: "easy", hint: "Hardest assignment is to color and do simple addition" },
    { emojis: ["🏫", "🗣️", "📜"], answer: "Sproul", difficulty: "hard", hint: "Musty Smelly and Hot" },
    { emojis: ["🧠", "📊", "🏫"], answer: "Watkins", difficulty: "hard", hint: "Humanities and historical ideologies" },
    { emojis: ["☕", "🥪", "💾"], answer: "Bytes", difficulty: "medium", hint: "Budget Starbucks.." },
    { emojis: ["🏋️", "🏀", "💪"], answer: "SRC", difficulty: "easy", hint: "Basketball courts are never open" },
    { emojis: ["🐻", "🛒", "🥤"], answer: "Scotties", difficulty: "medium", hint: "Store named after the UCR mascot" },
    { emojis: ["🍔", "🎟️", "🎉"], answer: "Hub", difficulty: "easy", hint: "The only food space in this god forsaken campus" }
];

let score = 0;
let currentIndex = 0;
let currentPuzzle;
let revealedEmojis = 1;
let attempt = 0;
let puzzleOrder = [];

// Shuffle all puzzle positions
function shufflePuzzles() {
    puzzleOrder = [...Array(puzzles.length).keys()];

    for (let i = puzzleOrder.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [puzzleOrder[i], puzzleOrder[j]] = [puzzleOrder[j], puzzleOrder[i]];
    }
}

// Start a puzzle
function startGame() {
    if (currentIndex >= puzzles.length) {
        showFinalScore();
        return;
    }

    currentPuzzle = puzzles[puzzleOrder[currentIndex]];
    revealedEmojis = 1;
    attempt = 0;

    document.getElementById("message").textContent = "";
    document.getElementById("answer-input").value = "";
    document.getElementById("answer-input").disabled = false;
    document.getElementById("submit-button").disabled = false;

    displayEmojis();
    updateStats();
}

// Display revealed emojis
function displayEmojis() {
    document.getElementById("emoji-display").textContent =
        currentPuzzle.emojis.slice(0, revealedEmojis).join(" ");
}

// Normalize guesses like the C++ cleanGuess function
function cleanGuess(guess) {
    let result = guess.toLowerCase();

    const dropWords = [
        "the ", "winston ", " hall",
        " library", " building", " center"
    ];

    for (const word of dropWords) {
        result = result.split(word).join("");
    }

    return result.trim();
}

// Check answer
function checkAnswer() {
    const input = document.getElementById("answer-input");
    const guess = input.value.trim();

    if (guess === "") {
        document.getElementById("message").textContent =
            "Enter a guess first!";
        return;
    }

    const points = [400, 300, 200, 100];

    if (cleanGuess(guess) === cleanGuess(currentPuzzle.answer)) {
        score += points[attempt];

        document.getElementById("message").textContent =
            `Correct! 🎉 It's ${currentPuzzle.answer}! +${points[attempt]} points`;

        currentIndex++;
        updateStats();

        input.disabled = true;
        document.getElementById("submit-button").disabled = true;

        setTimeout(startGame, 1800);
        return;
    }

    attempt++;

    if (attempt < 3) {
        revealedEmojis++;
        displayEmojis();

        document.getElementById("message").textContent =
            `Incorrect! Here's another emoji. Attempt ${attempt + 1} of 4.`;
    } else if (attempt === 3) {
        document.getElementById("message").textContent =
            `Last chance! Hint: ${currentPuzzle.hint}`;
    } else {
        document.getElementById("message").textContent =
            `The answer was ${currentPuzzle.answer}. Moving on...`;

        currentIndex++;

        input.disabled = true;
        document.getElementById("submit-button").disabled = true;

        setTimeout(startGame, 2200);
        return;
    }

    input.value = "";
    updateStats();
}

// Update score and question counter
function updateStats() {
    document.getElementById("score").textContent = score;

    const streakElement = document.getElementById("streak");
    if (streakElement) {
        streakElement.textContent = `${currentIndex + 1} / ${puzzles.length}`;
    }

    const counter = document.getElementById("question-counter");
    if (counter) {
        counter.textContent = `Question ${Math.min(currentIndex + 1, puzzles.length)} of ${puzzles.length}`;
    }
}

// Final score
function showFinalScore() {
    document.getElementById("emoji-display").textContent = "🏆";
    document.getElementById("message").textContent =
        `You've completed every location! Final score: ${score}`;

    document.getElementById("answer-input").disabled = true;
    document.getElementById("submit-button").disabled = true;
}

// Submit button
document.getElementById("submit-button").addEventListener("click", checkAnswer);

// Allow Enter key to submit
document.getElementById("answer-input").addEventListener("keydown", function(event) {
    if (event.key === "Enter") {
        checkAnswer();
    }
});

// Start the game
shufflePuzzles();
startGame();
