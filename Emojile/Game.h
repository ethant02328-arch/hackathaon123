
#ifndef GAME_H
#define GAME_H

#include "Puzzle.h"
#include <vector>

class Game {
private:
    std::vector<Puzzle> puzzles;
    int score;
    int streak;

public:
    Game();

    void loadPuzzles();
    void start();
    void playRound();
    void showMenu();
};

#endif
