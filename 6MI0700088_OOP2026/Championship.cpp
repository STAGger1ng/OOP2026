#include "Championship.h"

unsigned Championship::yearCounter = 2026;

void Championship::setYear()
{
	year = yearCounter++;
}

Championship::Championship()
	:isFinished(false), currentRound(0)
{
	setYear();
	try {
		unsigned addedTeams = 0;
		std::cout << "How many teams will participate?: ";
		std::cin >> numberOfTeams;
		while (!hasEnoughTeams())
		{
			std::cout << "Not enough teams for a fair championship! Try again!\n";
			std::cin >> numberOfTeams;
		}

		while(addedTeams < numberOfTeams)
		{
			std::cout << "What type of team to create?\n" <<
				"1 - Offensive Team\n" <<
				"2 - Balanced Team\n" <<
				"3 - Deffensive Team\n";
			unsigned short teamType;
			std::cin >> teamType;
			
			std::string teamName;
			std::string coach;
			std::string stadium;
			std::cin >> teamName >> coach >> stadium;
			Team* team;
			switch (teamType)
			{
			case 1:
				team = new OffensiveTeam(teamName, coach, stadium);
				break;
			case 2:
				team = new BalancedTeam(teamName, coach, stadium);
				break;
			case 3:
				team = new DefensiveTeam(teamName, coach, stadium);
				break;
			default:
				std::cout << "Invalid team type! Try again!\n";
				continue;
			}
			if (canAddTeam(team))
			{
				teams.push_back(team);
				addedTeams++;
			}else
			{
				std::cout << "  Cannot add " << teamName
					<< ". Team not valid, already selected, or limit reached. Try again.\n";
			}
		}
	}
	catch(...){
		throw std::exception("");
	}
	setAllRounds((teams.size() - 1) * 2);
	generateSchedule();
}

bool Championship::hasEnoughTeams() const
{
	return teams.size() >= 4 &&
		teams.size() % 2 == 0;

}

void Championship::generateSchedule()
{
	if (!hasEnoughTeams())
	{
		return;
	}
	matches.clear();
	unsigned short round = 1;
	for (unsigned i = 0; i < teams.size(); i++)
	{
		for (unsigned j = i + 1; j < teams.size(); j++)
		{
			matches.emplace_back(
				teams[i],
				teams[j],
				round,
				allRounds
			);

			matches.emplace_back(
				teams[j],
				teams[i],
				round,
				allRounds
			);
		}
	}


}

void Championship::playRound()
{
}

void Championship::playAllRounds()
{
}

void Championship::printTable() const
{
}

Team* Championship::getChampion() const
{
	return nullptr;
}

Team* Championship::getViceChampion() const
{
	return nullptr;
}

Team* Championship::getThirdPlace() const
{
	return nullptr;
}

std::vector<Player*> Championship::getAllPlayers() const
{
	std::vector<Player*> allPlayers;
	for (int i = 0; i < teams.size(); i++)
	{
		for (unsigned i = 0; i < teams[i]->getPlayers().size(); i++)
		{
			allPlayers.push_back( teams[i]->getPlayerAtIndex(i));
		}
	}

	return allPlayers;
}

std::vector<Player*> Championship::topScorers() const
{
	std::vector<Player*> allPlayers = getAllPlayers();
	std::vector<Player*> topScorers;
	unsigned highestGoals = 0;
	for (int i = 0; i < allPlayers.size(); i++)
	{
		if (allPlayers[i]->getMatches() > 7 
			&& allPlayers[i]->getGoalsScoredCurrently() > highestGoals)
		{
			topScorers.clear();
			topScorers.push_back(allPlayers[i]);
		}
		else if (allPlayers[i]->getGoalsScoredCurrently() == highestGoals) {
			if (allPlayers[i]->getMatches() < topScorers[0]->getMatches()) {
				topScorers.clear();
				topScorers.push_back(allPlayers[i]);
			}
			topScorers.push_back(allPlayers[i]);
		}
	}

	return topScorers;
}

void Championship::save(std::ofstream& out) const
{
}

void Championship::load(std::ifstream& in)
{
}

bool Championship::canAddTeam(Team* team)
{
	if (!team)
	{
		return false;
	}
	for (unsigned i = 0; i < teams.size(); i++)
	{
		if (team->getName() == teams[i]->getName()
			|| team->getStadium() == teams[i]->getStadium()
			|| team->getCoach() == teams[i]->getCoach())
		{
			std::cout << "Identical or too similar team can not be added to the same championship!\n";
			return false;
		}
	}
	return true;
}

void Championship::setAllRounds(const unsigned short allRounds)
{
	if (allRounds > 0)
	{
		this->allRounds = allRounds;
	}
	else {
		this->allRounds = 0;
	}
}
