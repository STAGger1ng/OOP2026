#pragma once	

#include <iostream>
#include <string>

#include "Position.h"

class Player
{
private:
    std::string firstName;
	std::string lastName;
    unsigned short number;
    Position position;
    double salary;
    double transferFee;
    unsigned matchesPlayed;
    unsigned goalsScoredCurrently;
    unsigned goalsScoredAllTime;

public:
    Player();

    const std::string& getFirstName() const;
	const std::string& getLastName() const; 
    const unsigned short getNumber() const;
    const Position getPosition() const;
    const unsigned getGoalsScoredCurrently() const;
    const unsigned getGoalsScoredAllTime() const;
    const unsigned getMatches() const;
    const double getSalary() const;
    const double getTransferFee() const;

	void setFirstName(const std::string& name);
	void setLastName(const std::string& name);
	void setNumber(const unsigned short number);
	void setPosition(const Position position);
	void setSalary(const double salary);
	void setTransferFee(const double transferFee);
	void setMatchesPlayed(const unsigned matches);
	void setGoalsScoredCurrently(const unsigned goals);
	void setGoalsScoredAllTime(const unsigned goals);

    void scoreGoal();
    void playMatch();

    void adjustSalary(unsigned teamMatches);

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
	friend std::istream& operator>>(std::istream& is, Player& p);
};

