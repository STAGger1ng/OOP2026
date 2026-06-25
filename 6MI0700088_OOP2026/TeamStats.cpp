#include "TeamStats.h"

void TeamStats::updateAfterMatch(unsigned short scored, unsigned short recieved)
{
	goalsScored += scored;
	goalsReceived += recieved;
	if (scored > recieved)
	{
		wins++;
		points += 3;
	}
	else if (scored == recieved)
	{
		draws++;
		points += 1;
	}
	else
	{
		losses++;
	}
}

void TeamStats::resetForNewChamp()
{
	wins = draws = losses = points = goalsScored = goalsReceived = 0;
}

void TeamStats::save(std::ofstream& out) const
{
	out << wins << " " << draws << " " << losses << " "
		<< goalsScored << " " << goalsReceived << " " << points << "\n";
}

void TeamStats::load(std::ifstream& in)
{
	in >> wins >> draws >> losses >> goalsScored >> goalsReceived >> points;
}

int TeamStats::getPoints() const
{
	return points;
}

int TeamStats::goalDifference() const
{
	return goalsScored - goalsReceived;
}