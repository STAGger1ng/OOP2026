#pragma once

#include "Team.h"

class OffensiveTeam : public Team
{
protected:
	const unsigned short requiredRoleDistribution[5] = { 2, 2, 2, 2, 8 }; // GK, DF, MF, WN, FW
public:
	OffensiveTeam(const std::string& teamName, const std::string& coach, const std::string& stadium, double budget = 1000);
	bool canBuyPlayer(const Player& player) const override;
	bool isValidTeam() const override;
};

