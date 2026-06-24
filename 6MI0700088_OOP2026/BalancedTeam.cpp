#include "BalancedTeam.h"

bool BalancedTeam::canBuyPlayer(const Player& player) const
{
	//if (rolesDistribution[static_cast<int>(player.getPosition())] + 1 > requiredRoleDistribution[static_cast<int>(player.getPosition())])
	//{
	//	return false;
	//}
	return true;
}

bool BalancedTeam::isValidTeam() const
{
	for (int i = 0; i < 5; i++)
	{
		if (requiredRoleDistribution[i] > rolesDistribution[i])
		{
			return false;
		}
	}
	return true;
}

