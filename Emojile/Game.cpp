#ifndef GAME_H
#define GAME_H
#include "Puzzle.h"
#include <vector>
#include <string>

class Game {
private:
    std::vector<Puzzle> puzzles;
    int score;
    int streak;
public:
    Game();
    bool loadPuzzles(std::string filename);
    void playRound(Puzzle& p);
    void run();
};
#endif
