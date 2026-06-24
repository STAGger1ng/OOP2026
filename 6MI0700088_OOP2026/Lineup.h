#pragma once

#include "Team.h"

class Lineup
{
private:
	static const unsigned short MAX_PLAYERS_IN_LINEUP;
	static const unsigned short MAX_ROLE_COUNT;
    static const unsigned short MIN_ROLES_DISTRIBUTION[];

	const Team& team;
	std::vector <Player*> chosenPlayers;

	unsigned short rolesDistribution[5] = { 0, 0, 0, 0, 0 };

public: 
    explicit Lineup(Team& team);

	bool canAddPlayer(const Player* player) const;

    bool addPlayer( const std::string& playerFirstName, const std::string& playerSecondName);

    bool isValidLineupWithPlayer(const Player* player);
    bool isValidLineup() const;

    void autoIncludeLowMatchPlayers( bool lastThreeRounds);

    void updateStatsAfterMatch();
};

