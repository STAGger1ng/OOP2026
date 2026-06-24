#include "Lineup.h"

const unsigned short Lineup::MAX_PLAYERS_IN_LINEUP = 11;
const unsigned short Lineup::MAX_ROLE_COUNT = 5;
const unsigned short Lineup::MIN_ROLES_DISTRIBUTION[Lineup::MAX_ROLE_COUNT]{ 1,2,2,2,2 };

Lineup::Lineup(Team& team)
    : team(team)
{
    chosenPlayers.reserve(MAX_PLAYERS_IN_LINEUP);
}

bool Lineup::canAddPlayer(const Player* player)
{
	if (!player)
	{
		return false;
	}

	if (chosenPlayers.size() >= MAX_PLAYERS_IN_LINEUP)
	{
		return false;
	}
	for (const Player* currPlayer : chosenPlayers)
	{
		if ((currPlayer->getFirstName() == player->getFirstName()
			&& currPlayer->getLastName() == player->getLastName())
			|| currPlayer->getNumber() == player->getNumber())
		{
			return false;
		}
		if (isValidLineupWithPlayer(player))
		{
			return true;
		}
	}
    return false;
}

bool Lineup::addPlayer(const std::string& playerFirstName, const std::string& playerLastName)
{
	for (int i = 0; i < team.getPlayers().size(); ++i)
	{
		if (team.getPlayers()[i].getFirstName() == playerFirstName && team.getPlayers()[i].getLastName() == playerLastName)
		{
			if (canAddPlayer(&team.getPlayers()[i]))
			{
				chosenPlayers.push_back(team.getPlayerAtIndex(i));
				return true;
			}
		}
	}
    return false;
}

bool Lineup::isValidLineupWithPlayer(const Player* player)
{
	if (chosenPlayers.size() + 1 > MAX_PLAYERS_IN_LINEUP)
	{
		return false;
	}

	rolesDistribution[static_cast<int>(player->getPosition())]++;

	if (rolesDistribution[0] != MIN_ROLES_DISTRIBUTION[0])
	{
		rolesDistribution[static_cast<int>(player->getPosition())]--;
		return false;
	}

	unsigned sumOfPositions = 0;
	for (int i = 1; i < MAX_ROLE_COUNT; i++)
	{
		sumOfPositions += rolesDistribution[i];
		if (sumOfPositions > 10)
		{
			return false;
		}
		if (rolesDistribution[i] > 4 )
		{
			rolesDistribution[static_cast<int>(player->getPosition())]--;
			return false;
		}
	}

	rolesDistribution[static_cast<int>(player->getPosition())]--;
	return true;
}

bool Lineup::isValidLineup() const
{
	if (chosenPlayers.size() != MAX_PLAYERS_IN_LINEUP)
	{
		return false;
	}
	if (rolesDistribution[0] != MIN_ROLES_DISTRIBUTION[0])
	{
		return false;
	}
	for (int i = 1; i < MAX_ROLE_COUNT; i++)
	{
		if (rolesDistribution[i] < MIN_ROLES_DISTRIBUTION[i])
		{
			return false;
		}
	}
	
	return true;
}

void Lineup::autoIncludeLowMatchPlayers(bool lastThreeRounds)
{
	for (int i = 0; i < team.getPlayers().size(); ++i)
	{
		if (team.getPlayerAtIndex(i)->getMatches() < 3)
		{
			addPlayer(team.getPlayerAtIndex(i)->getFirstName(), team.getPlayerAtIndex(i)->getLastName());
		}
	}
}

void Lineup::updateStatsAfterMatch()
{
	for (int i = 0; i < chosenPlayers.size(); ++i)
	{
		team.getPlayerAtIndex(i)
	}

}
