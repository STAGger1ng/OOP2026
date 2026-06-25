#pragma once

#include <vector>
#include <fstream>

#include "Player.h"
#include "TeamStats.h"

class Team
{
private:
    bool isTooSimilarPlayer(const Player& player) const;
	const int findPlayerByNumber(const unsigned short playerNumber) const;
protected:
	static const unsigned short MAX_PLAYERS = 20;
    std::string teamName = "Unknown";
    std::string coach = "Unknown";
    std::string stadium = "Unknown";

    double budget = 10000;

    std::vector<Player> players;

    TeamStats stats;
    unsigned short rolesDistribution[5] = { 0, 0, 0, 0, 0 }; // GK, DF, MF,WN, FW

public:
	Team(const std::string& teamName,
		 const std::string& coach,
		 const std::string& stadium,
		 double budget = 1000);
    virtual ~Team() = default;

    const std::string& getName() const;
	const std::string& getCoach() const;
	const std::string& getStadium() const;
	double getBudget() const;
    const std::vector<Player>& getPlayers() const;
    std::vector<Player>& getPlayers();
    const Player& getPlayerAtIndex( const unsigned index) const;
    Player* getPlayerAtIndex(const unsigned index);
    const TeamStats& getStats() const;

    void setName( const std::string& name);
    void setCoach(const std::string& coach);
    void setStadium(const std::string& stadium);
    void setBudget( double budget);

    bool addPlayer(const Player& player);
    bool removePlayer(const unsigned short playerNumber);
	bool transferPlayerTo(const unsigned short ourPlayerNumber, Team& otherTeam, const unsigned short otherPlayerNumber);

    virtual bool canBuyPlayer(const Player& player) const = 0;
    virtual bool isValidTeam() const = 0;
    
    void startNewSeason();
    void updateAfterMatch(unsigned short scored, unsigned short conceded);

    void saveToFile(std::ofstream& out) const;
    void loadFromFile(std::ifstream& in);
    
    friend std::ostream& operator<<(std::ostream& os, const Team& t);
    friend std::istream& operator>>(std::istream& is, Team& t);
};
