
#include "Puzzle.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Puzzle::Puzzle(std::vector<std::string> e,
               std::string a,
               std::string d,
               std::string h) {
    emojis = e;
    answer = a;
    difficulty = d;
    hint = h;
    revealedEmojis = 1;
}

void Puzzle::display() {
    std::cout << "\nGuess the emojis:\n";

    for (int i = 0; i < revealedEmojis; i++) {
        std::cout << emojis[i] << " ";
    }

    std::cout << "\n";
}

void Puzzle::revealNextEmoji() {
    if (revealedEmojis < emojis.size()) {
        revealedEmojis++;
    }
}

bool Puzzle::checkAnswer(std::string guess) {
    std::transform(guess.begin(), guess.end(),
                   guess.begin(), ::tolower);

    std::string correct = answer;

    std::transform(correct.begin(), correct.end(),
                   correct.begin(), ::tolower);

    return guess == correct;
}

std::string Puzzle::getAnswer() {
    return answer;
}

std::string Puzzle::getHint() {
    return hint;
}
std::string Puzzle::getAnswer() {
    return answer;
}
std::string Puzzle::getHint() {
    return hint;
}

#include "Puzzle.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Puzzle::Puzzle(std::vector<std::string> e,
               std::string a,
               std::string d,
               std::string h) {
    emojis = e;
    answer = a;
    difficulty = d;
    hint = h;
    revealedEmojis = 1;
}

void Puzzle::display() {
    std::cout << "\nGuess the emojis:\n";

    for (int i = 0; i < revealedEmojis; i++) {
        std::cout << emojis[i] << " ";
    }

    std::cout << "\n";
}

void Puzzle::revealNextEmoji() {
    if (revealedEmojis < emojis.size()) {
        revealedEmojis++;
    }
}

bool Puzzle::checkAnswer(std::string guess) {
    std::transform(guess.begin(), guess.end(),
                   guess.begin(), ::tolower);

    std::string correct = answer;

    std::transform(correct.begin(), correct.end(),
                   correct.begin(), ::tolower);

    return guess == correct;
}

std::string Puzzle::getAnswer() {
    return answer;
}

std::string Puzzle::getHint() {
    return hint;
}
