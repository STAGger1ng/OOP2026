#pragma once

#include "Team.h"

class BalancedTeam : public Team
{
protected:
	const unsigned short requiredRoleDistribution[5] = { 2, 4, 4, 4, 4 }; // GK, DF, MF, WN, FW
public:
	using Team::Team;
	bool canBuyPlayer(const Player& player) const override;
	bool isValidTeam() const override;
};

