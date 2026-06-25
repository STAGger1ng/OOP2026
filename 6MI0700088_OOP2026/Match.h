#pragma once

#include "Lineup.h"


struct GoalScorer
{
    std::string firstName;
    std::string lastName;
    bool isHomeTeam;
};

class Match
{
private:
    Team* homeTeam;
    Team* awayTeam;
    Lineup homeLineup;
    Lineup awayLineup;
    unsigned short homeGoals;
    unsigned short awayGoals;
    unsigned short roundNumber;
    unsigned short totalRounds;
    std::vector<GoalScorer> scorers;

    void selectLineup(Lineup& lineup, const std::string& teamName);
    void addGoalScorer(unsigned short goalIndex);

public:
    Match(Team* home, Team* away, unsigned short round, unsigned short totalRounds);

    bool selectLineups();
    void enterResult();
    void addGoals();
    void updateStats();
    void play();

    Team* getHomeTeam() const;
    Team* getAwayTeam() const;
    unsigned short getHomeGoals() const;
    unsigned short getAwayGoals() const;
    unsigned short getRoundNumber() const;
    const std::vector<GoalScorer>& getScorers() const;
    const Lineup& getHomeLineup() const;
    const Lineup& getAwayLineup() const;
};
