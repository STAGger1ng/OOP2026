#pragma once

#include "Team.h"
#include "BalancedTeam.h"
#include "OffensiveTeam.h"
#include "DefensiveTeam.h"
#include "Match.h"

class Championship
{
private:
	static unsigned yearCounter;

	bool isFinished;
	unsigned short numberOfTeams;
	unsigned short currentRound;
	unsigned short allRounds;
	unsigned year;
	std::vector<Team*> teams;
	std::vector<Match> matches;

	void setYear();
public:
	Championship();
	bool hasEnoughTeams() const;
	void generateSchedule();
	void playRound();
	void playAllRounds();
	void printTable() const;
	Team* getChampion() const;
	Team* getViceChampion() const;
	Team* getThirdPlace() const;
	std::vector<Player*> getAllPlayers() const;
	std::vector<Player*> topScorers() const;

	void save(std::ofstream& out) const;
	void load(std::ifstream& in);
	

	bool addTeam(Team* team);
	void setAllRounds(const unsigned short allRounds);

};

