#include "TeamStats.h"

void TeamStats::updateAfterMatch(unsigned short scored, unsigned short recieved)
{
	goalsScored = scored;
	goalsReceived = recieved;
	if (goalsScored > goalsReceived)
	{
		wins++;
		points += 3;
	}
	else if (goalsScored == goalsReceived)
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
	wins, draws, losses, points, goalsScored, goalsReceived = 0;
}

int TeamStats::getPoints() const
{
	return points;
}

int TeamStats::goalDifference() const
{
	return goalsScored-goalsReceived;
}
