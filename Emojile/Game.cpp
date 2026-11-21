#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

static std::vector<int> order;
static int nextPuzzle = 0;
static std::string cleanGuess(std::string g) {
    std::transform(g.begin(), g.end(), g.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::vector<std::string> dropWords = {"the ", "winston ", " hall",
                                          " library", " building", " center"};
    for (const std::string& w : dropWords) {
        size_t pos;
        while ((pos = g.find(w)) != std::string::npos) {
            g.erase(pos, w.size());
        }
    }
    size_t a = g.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = g.find_last_not_of(" \t\r\n");
    return g.substr(a, b - a + 1);
}

Game::Game() {
    score = 0;
}

// Answers match the names in Puzzle.txt. Each puzzle: 3 emojis, answer,
// difficulty, and a text hint shown on the last try.
void Game::loadPuzzles() {
    puzzles.push_back(Puzzle({"🧑🏾‍🏫", "🏫", "🔬"}, "Skye", "hard",
        "Supplemental Instructor Hotspot (ebk)"));
    puzzles.push_back(Puzzle({"⚙️", "🔧", "🏗️"}, "Bourns", "medium",
        "The lesser known CS building for engineers"));
    puzzles.push_back(Puzzle({"💻", "🤖", "⚡"}, "Chung", "medium",
        "Heart attack for CS students"));
    puzzles.push_back(Puzzle({"🪑", "👩‍🏫", "🧪"}, "Pierce", "medium",
        "Biologically substantial"));
    puzzles.push_back(Puzzle({"📝", "🏛️", "🎓"}, "Olmsted", "hard",
        "Statistically speaking and pschologically demanding"));
    puzzles.push_back(Puzzle({"📚", "🤫", "🔔"}, "Rivera", "easy",
        "The worst library"));
    puzzles.push_back(Puzzle({"📚📚", "📚📚📚", "🌙"}, "Orbach", "medium",
        "The better library"));
    puzzles.push_back(Puzzle({"🔭", "⚛️", "🧲"}, "Physics", "easy",
        "Legit in the name"));
    puzzles.push_back(Puzzle({"🎤", "🪑", "👥"}, "Lecture Hall", "medium",
        "Most of the classes are here honestly big ting"));
    puzzles.push_back(Puzzle({"🧑‍🏫", "📖", "🏢"}, "UTLF", "hard",
        "The one building that never shows up on maps"));
    puzzles.push_back(Puzzle({"🧬", "🔬", "🧫"}, "Genomics", "medium",
        "Jeans"));
    puzzles.push_back(Puzzle({"💼", "📈", "💰"}, "Business", "easy",
        "Hardest assignment is to color and do simple addition"));
    puzzles.push_back(Puzzle({"🏫", "🗣️", "📜"}, "Sproul", "hard",
        "Musty Smelly and Hot"));
    puzzles.push_back(Puzzle({"🧠", "📊", "🏫"}, "Watkins", "hard",
        "Humanities and historical ideologies"));
    puzzles.push_back(Puzzle({"☕", "🥪", "💾"}, "Bytes", "medium",
        "Budget Starbucks.."));
    puzzles.push_back(Puzzle({"🏋️", "🏀", "💪"}, "SRC", "easy",
        "Basketball courts are never open"));
    puzzles.push_back(Puzzle({"🐻", "🛒", "🥤"}, "Scotties", "medium",
        "Store named after the UCR mascot"));
    puzzles.push_back(Puzzle({"🍔", "🎟️", "🎉"}, "Hub", "easy",
        "The only food space in this god forsaken campus"));

    for (int i = 0; i < (int)puzzles.size(); i++) order.push_back(i);
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::shuffle(order.begin(), order.end(), rng);
    nextPuzzle = 0;
}

void Game::showMenu() {
    std::cout << "\n==============================\n";
    std::cout << "      🐻  R I V ' D L E  🐻\n";
    std::cout << " Guess the UCR spot from emojis\n";
    std::cout << "==============================\n";
    std::cout << "1) Play\n";
    std::cout << "2) Quit\n";
    std::cout << "Choose 1-2: ";
}

void Game::playRound() {
    if (nextPuzzle >= (int)order.size()) {
        std::cout << "\n🎉 You've played every location! Final score: "
                  << score << "\n";
        return;
    }

    Puzzle& p = puzzles[order[nextPuzzle]];
    nextPuzzle++;

    int points[4] = {400, 300, 200, 100};

    std::cout << "\n--- Puzzle " << nextPuzzle << " of " << order.size() << " ---\n";

    for (int i = 0; i < 4; i++) {
        p.display();
        if (i == 3) {
            std::cout << "Hint: " << p.getHint() << "\n";
        }

        std::cout << "Your guess (" << i + 1 << "/4): ";
        std::string guess;
        if (!std::getline(std::cin, guess)) return;

        if (cleanGuess(guess) == cleanGuess(p.getAnswer())) {
            score += points[i];
            std::cout << "✅ Correct! It's " << p.getAnswer()
                      << "!  +" << points[i] << " points\n";
            std::cout << "Score: " << score << "\n";
            return;
        }

        if (i < 2) {
            std::cout << "❌ Nope! Here's another emoji...\n";
            p.revealNextEmoji();
        } else if (i == 2) {
            std::cout << "❌ Nope! Last chance, here's a hint...\n";
        }
    }

    std::cout << "\nThe answer was: " << p.getAnswer() << "\n";
    std::cout << "Score: " << score << "\n";
}

void Game::start() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // so emojis show in the Windows terminal
#endif

    while (true) {
        showMenu();
        std::string choice;
        if (!std::getline(std::cin, choice)) break;

        if (choice == "1") {
            playRound();
        } else if (choice == "2") {
            break;
        } else {
            std::cout << "Type 1 or 2.\n";
        }
    }

    std::cout << "\nFinal score: " << score << "\nThanks for playing! Go Highlanders! 🐻\n";
}
