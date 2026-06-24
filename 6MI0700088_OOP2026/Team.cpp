#include "Team.h"

bool Team::isTooSimilarPlayer(const Player& player) const
{
	for (int i = 0; i < players.size(); ++i)
	{
		if (player.getNumber() == players.at(i).getNumber() 
			||
			(  player.getFirstName() == players.at(i).getFirstName()
			&& player.getLastName() == players.at(i).getLastName() )
			)
		{
			return true;
		}
	}
	return false;
}

const int Team::findPlayerByNumber(const unsigned short playerNumber) const
{
	for (int i = 0; i < players.size(); ++i)
	{
		if (playerNumber == players.at(i).getNumber())
		{
			return i;
		}
	}
	return -1;
}

Team::Team(const std::string& teamName, const std::string& coach, const std::string& stadium, double budget = 10000)
{
	setName(teamName);
	setCoach(coach);
	setStadium(stadium);
	setBudget(budget);
}

const std::string& Team::getName() const
{
	return teamName;
}

const std::string& Team::getCoach() const
{
	return coach;
}

const std::string& Team::getStadium() const
{
	return stadium;
}

const std::vector<Player>& Team::getPlayers() const
{
	return players;
}

const Player& Team::getPlayerAtIndex(const unsigned index) const
{
	return players[index];
}

Player* Team::getPlayerAtIndex(const unsigned index)
{
	return &players[index];
}

const TeamStats& Team::getStats() const
{
	return stats;
}

void Team::setName(const std::string& name)
{
	if (!name.empty())
	{
		this->teamName = name;
	}
}

void Team::setCoach(const std::string& coach)
{
	if (!coach.empty())
	{
		this->coach = coach;
	}
}

void Team::setStadium(const std::string& stadium)
{
	if (!stadium.empty())
	{
		this->stadium = stadium;
	}
}

void Team::setBudget( const double budget)
{
	if (budget > 0)
	{
		this->budget = budget;
	}
}

bool Team::addPlayer(const Player& player)
{
	if (players.size() < MAX_PLAYERS
		&& player.getTransferFee() > budget
		&& isTooSimilarPlayer(player))
	{
		return false;
	}
	else
	{
		players.push_back(player);
		budget -= player.getTransferFee();
		rolesDistribution[static_cast<int>(player.getPosition())]++;
		return true;
	}
    
}

bool Team::removePlayer(const unsigned short playerNumber)
{
	const int playerIndx = findPlayerByNumber(playerNumber);
	if (playerIndx == -1)
	{
		return false;
	}
	Position oldPosition = players.at(playerIndx).getPosition();
	players.at(playerIndx).setPosition(Position::Unknown);
	if (isValidTeam())
	{
		rolesDistribution[static_cast<int>(players.at(playerIndx).getPosition())]--;
		// budget += players.at(playerIndx).getTransferFee();
		players.erase(players.begin() + playerIndx);
		return true;
	}
	players.at(playerIndx).setPosition(oldPosition);

	return false;
}

bool Team::transferPlayerTo(const unsigned short currTeamPlayerNumber, Team& otherTeam, const unsigned short otherTeamPlayerNumber)
{
	const int currTeamPlayerIndx = findPlayerByNumber(currTeamPlayerNumber);
	const int otherTeamPlayerIndx = otherTeam.findPlayerByNumber(otherTeamPlayerNumber);

	if (currTeamPlayerIndx == -1 || otherTeamPlayerIndx == -1)
	{
		return false;
	}	

	if (budget + players.at(currTeamPlayerIndx).getTransferFee() < otherTeam.players.at(otherTeamPlayerIndx).getTransferFee()
		|| otherTeam.budget + otherTeam.players.at(otherTeamPlayerIndx).getTransferFee() < players.at(currTeamPlayerIndx).getTransferFee())
	{
		return false;
	}

	// Swap the positions of the two players temporarily to check if the teams remain valid after the transfer
	Position currTeamPosition = players.at(currTeamPlayerIndx).getPosition();
	players.at(currTeamPlayerIndx).setPosition(otherTeam.getPlayers().at(otherTeamPlayerIndx).getPosition());
	otherTeam.players.at(otherTeamPlayerIndx).setPosition(currTeamPosition);

	if (isValidTeam() && otherTeam.isValidTeam())
	{
		return false;
	}

	// Swap back the positions of the two players to their original positions
	otherTeam.players.at(otherTeamPlayerIndx).setPosition(players.at(currTeamPlayerIndx).getPosition());
	players.at(currTeamPlayerIndx).setPosition(currTeamPosition);

	// Create copies of the players to be transferred
	Player copyCurrTeamPlayer = players.at(currTeamPlayerIndx);
	Player copyOtherTeamPlayer = otherTeam.players.at(otherTeamPlayerIndx);

	// Remove the players from their respective teams and update the rolesDistribution and budget accordingly
	rolesDistribution[static_cast<int>(players.at(currTeamPlayerIndx).getPosition())]--;
	budget += players.at(currTeamPlayerIndx).getTransferFee();
	players.erase(players.begin() + currTeamPlayerIndx);

	otherTeam.rolesDistribution[static_cast<int>(otherTeam.players.at(otherTeamPlayerIndx).getPosition())]--;
	otherTeam.budget += otherTeam.players.at(otherTeamPlayerIndx).getTransferFee();
	otherTeam.players.erase(otherTeam.players.begin() + otherTeamPlayerIndx);

	// Add the players to their new teams and update the rolesDistribution and budget accordingly
	players.push_back(copyOtherTeamPlayer);
	rolesDistribution[static_cast<int>(copyOtherTeamPlayer.getPosition())]++;
	budget -= copyOtherTeamPlayer.getTransferFee();

	otherTeam.players.push_back(copyCurrTeamPlayer);
	otherTeam.rolesDistribution[static_cast<int>(copyCurrTeamPlayer.getPosition())]++;
	otherTeam.budget -= copyCurrTeamPlayer.getTransferFee();
	
	return true;
}

void Team::startNewSeason()
{
	stats.resetForNewChamp();
	for (int i = 0; i < players.size(); ++i)
	{
		players.at(i).setMatchesPlayed(0);
		players.at(i).setGoalsScoredCurrently(0);
	}
}

void Team::updateAfterMatch(unsigned short scored, unsigned short conceded)
{
	stats.updateAfterMatch(scored, conceded);
}

std::ostream& operator<<(std::ostream& os, const Team& t)
{
	os << t.teamName << " " << t.coach << " " << t.stadium << " " << t.budget << " " << t.players.size() << std::endl;
	for (const Player& player : t.players)
	{
		os << player << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, Team& t)
{
	is >> t.teamName >> t.coach >> t.stadium >> t.budget;
	unsigned numPlayers;
	is >> numPlayers;
	if (numPlayers > Team::MAX_PLAYERS)
	{
		numPlayers = Team::MAX_PLAYERS;
		//throw std::runtime_error("Number of players exceeds the maximum allowed.");
	}
	for (unsigned i = 0; i < numPlayers; ++i)
	{
		Player player;
		is >> player;
		t.addPlayer(player);
	}

	return is;
}
