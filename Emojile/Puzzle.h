#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>

class Puzzle {
private:
    std::vector<std::string> emojis;
    std::string answer;
    std::string difficulty;
    std::string hint;
    int revealedEmojis;

public:
    Puzzle(std::vector<std::string> e,
           std::string a,
           std::string d,
           std::string h);

    void display();
    void revealNextEmoji();
    bool checkAnswer(std::string guess);

    std::string getAnswer();
    std::string getHint();
};

#endif
