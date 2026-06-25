#pragma once

#include "Team.h"

class DefensiveTeam : public Team
{
protected:
	const short requiredRoleDistribution[5] = { 2, 6, 6, 2, 2 }; // GK, DF, MF, WN, FW
public:
	DefensiveTeam(const std::string& teamName, const std::string& coach, const std::string& stadium, double budget = 1000);
	bool canBuyPlayer(const Player& player) const override;
	bool isValidTeam() const override;
};

