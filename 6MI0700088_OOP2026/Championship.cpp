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
		//while(addedTeams < numberOfTeams)
		//{
		//	std::string teamName;
		//	std::string coach;
		//	std::string stadium;
		//	std::cin >> teamName >> coach >> stadium;
		//	BalancedTeam team(teamName, coach, stadium);

		//	if ()
		//	{
		//		addTeam(team);
		//		addedTeams++;
		//	}
		//	else
		//	{
		//		std::cout << "  Cannot add " << teamName
		//			<< ". Team not valid, already selected, or limit reached. Try again.\n";
		//	}
		//}
	}
	catch(...){
		throw std::exception("");
	}
	generateSchedule();
}

bool Championship::hasEnoughTeams() const
{
	if (numberOfTeams < 4 || numberOfTeams % 2)
	{
		return false;
	}
	//setAllRounds((teams.size() - 1) * 2);
	return true;
}

void Championship::generateSchedule()
{
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
	return std::vector<Player*>();
}

std::vector<Player*> Championship::topScorers() const
{
	return std::vector<Player*>();
}

void Championship::save(std::ofstream& out) const
{
}

void Championship::load(std::ifstream& in)
{
}

bool Championship::addTeam(Team* team)
{
}

void setAllRounds(const unsigned short allRounds) {
	if (allRounds > 0)
	{
		this->allRounds = allRounds;
	}
}
