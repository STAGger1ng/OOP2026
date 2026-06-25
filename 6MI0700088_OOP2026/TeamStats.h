#pragma once
#include <fstream>

struct TeamStats
{
private:
    unsigned wins = 0;
    unsigned draws = 0;
    unsigned losses = 0;

    unsigned goalsScored = 0;
    unsigned goalsReceived = 0;

    unsigned points = 0;

public:
    void updateAfterMatch(
        unsigned short scored,
        unsigned short recieved);

    void resetForNewChamp();

    int getPoints() const;

    int goalDifference() const;

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
};
