#ifndef GAME_H
#define GAME_H

#include "Puzzle.h"
#include <vector>
#include <string>

class Game {
private:
    std::vector<Puzzle> puzzles;
    int score;

public:
    Game();
    void loadPuzzles();
    void start();
    void playRound();
    void showMenu();
};

#endif
