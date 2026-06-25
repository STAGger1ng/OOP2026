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
		for (unsigned i = 0; i < teams.size(); ++i)
			delete teams[i];
		teams.clear();
		throw std::exception("Championship creation failed.");
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
	unsigned short n = numberOfTeams;
	unsigned short halfRounds = n - 1;

	// Circle method: fix teams[n-1], rotate teams[0..n-2]
	std::vector<unsigned short> rotation(n - 1);
	for (unsigned short i = 0; i < n - 1; ++i)
		rotation[i] = i;

	for (unsigned short round = 1; round <= halfRounds; ++round)
	{
		// Fixed team (index n-1) plays rotation[0]
		matches.emplace_back(teams[n - 1], teams[rotation[0]], round, allRounds);

		// Pair the rest symmetrically from both ends of the rotation array
		for (unsigned short i = 1; i <= (n - 2) / 2; ++i)
		{
			matches.emplace_back(teams[rotation[i]], teams[rotation[n - 1 - i]], round, allRounds);
		}

		// Rotate: move last element to front
		unsigned short last = rotation[n - 2];
		for (int k = n - 2; k > 0; --k)
			rotation[k] = rotation[k - 1];
		rotation[0] = last;
	}

	// Second half: repeat with home/away swapped (rounds halfRounds+1 .. allRounds)
	unsigned short firstHalfSize = (unsigned short)matches.size();
	for (unsigned short i = 0; i < firstHalfSize; ++i)
	{
		unsigned short newRound = matches[i].getRoundNumber() + halfRounds;
		matches.emplace_back(matches[i].getAwayTeam(), matches[i].getHomeTeam(), newRound, allRounds);
	}
}

void Championship::playRound()
{
	if (currentRound >= allRounds)
	{
		std::cout << "All rounds have been played.\n";
		return;
	}
	currentRound++;
	std::cout << "\n=== Round " << currentRound << " / " << allRounds << " ===\n";
	for (unsigned i = 0; i < matches.size(); ++i)
	{
		if (matches[i].getRoundNumber() == currentRound)
		{
			std::cout << matches[i].getHomeTeam()->getName()
				<< " vs " << matches[i].getAwayTeam()->getName() << "\n";
			matches[i].play();
		}
	}
	if (currentRound >= allRounds)
	{
		isFinished = true;
	}
}

void Championship::playAllRounds()
{
	while (currentRound < allRounds)
	{
		playRound();
	}
}

void Championship::printTable() const
{
	std::vector<Team*> sorted = getSortedTeams();
	std::cout << "\n=== Championship " << year << " - Round "
		<< currentRound << " / " << allRounds << " ===\n";
	std::cout << "Pos | Team                 | Pts | GD\n";
	std::cout << "----+----------------------+-----+-----\n";
	for (unsigned i = 0; i < sorted.size(); ++i)
	{
		std::cout << " " << (i + 1) << "  | "
			<< sorted[i]->getName() << " | "
			<< sorted[i]->getStats().getPoints() << " | "
			<< sorted[i]->getStats().goalDifference() << "\n";
	}
}

const unsigned Championship::getYear() const
{
	return year;
}

Team* Championship::getChampion() const
{
	if (teams.empty()) return nullptr;
	return getSortedTeams()[0];
}

Team* Championship::getViceChampion() const
{
	if (teams.size() < 2) return nullptr;
	return getSortedTeams()[1];
}

Team* Championship::getThirdPlace() const
{
	if (teams.size() < 3) return nullptr;
	return getSortedTeams()[2];
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
	out << year << " " << isFinished << " " << numberOfTeams
		<< " " << currentRound << " " << allRounds << "\n";

	for (unsigned i = 0; i < teams.size(); ++i)
	{
		if (dynamic_cast<OffensiveTeam*>(teams[i]) != nullptr)
			out << 1 << "\n";
		else if (dynamic_cast<BalancedTeam*>(teams[i]) != nullptr)
			out << 2 << "\n";
		else
			out << 3 << "\n";

		teams[i]->saveToFile(out);
	}

	out << matches.size() << "\n";
	for (unsigned i = 0; i < matches.size(); ++i)
	{
		unsigned homeIdx = 0, awayIdx = 0;
		for (unsigned j = 0; j < teams.size(); ++j)
		{
			if (teams[j] == matches[i].getHomeTeam())
				homeIdx = j;
			if (teams[j] == matches[i].getAwayTeam())
				awayIdx = j;
		}
		out << homeIdx << " " << awayIdx << " " << matches[i].getRoundNumber() << "\n";
	}
}

void Championship::load(std::ifstream& in)
{
	for (unsigned i = 0; i < teams.size(); ++i)
		delete teams[i];
	teams.clear();
	matches.clear();

	int finished;
	in >> year >> finished >> numberOfTeams >> currentRound >> allRounds;
	isFinished = (finished != 0);

	for (unsigned i = 0; i < numberOfTeams; ++i)
	{
		unsigned short teamType;
		in >> teamType;

		Team* team = nullptr;
		switch (teamType)
		{
		case 1:
			team = new OffensiveTeam("tmp", "tmp", "tmp");
			break;
		case 2:
			team = new BalancedTeam("tmp", "tmp", "tmp");
			break;
		default:
			team = new DefensiveTeam("tmp", "tmp", "tmp");
			break;
		}
		team->loadFromFile(in);
		teams.push_back(team);
	}

	unsigned matchCount;
	in >> matchCount;
	for (unsigned i = 0; i < matchCount; ++i)
	{
		unsigned homeIdx, awayIdx, roundNum;
		in >> homeIdx >> awayIdx >> roundNum;
		matches.emplace_back(teams[homeIdx], teams[awayIdx],
			(unsigned short)roundNum, allRounds);
	}
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

Championship::~Championship()
{
	for (unsigned i = 0; i < teams.size(); ++i)
	{
		delete teams[i];
	}
}

std::vector<Team*> Championship::getSortedTeams() const
{
	std::vector<Team*> sorted = teams;
	unsigned n = (unsigned)sorted.size();
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j + 1 < n - i; ++j)
		{
			bool shouldSwap =
				sorted[j]->getStats().getPoints() < sorted[j + 1]->getStats().getPoints() ||
				(sorted[j]->getStats().getPoints() == sorted[j + 1]->getStats().getPoints() &&
					sorted[j]->getStats().goalDifference() < sorted[j + 1]->getStats().goalDifference());
			if (shouldSwap)
			{
				Team* tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
		}
	}
	return sorted;
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

