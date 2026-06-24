#include "Player.h"

static bool isValidName(const std::string& name)
{
	return name.length() > 0 && name.length() < 50;
}

Player::Player() : firstName("Unknown"), lastName("Unknown"), number(0), position(Position(6)), salary(1), transferFee(1), matchesPlayed(0), goalsScoredCurrently(0), goalsScoredAllTime(0)
{
}

const std::string& Player::getFirstName() const
{
	return firstName;
}

const std::string& Player::getLastName() const
{
	return lastName;
}

const unsigned short Player::getNumber() const
{
    return number;
}

const Position Player::getPosition() const
{
    return position;
}

const unsigned Player::getGoalsScoredCurrently() const
{
    return goalsScoredCurrently;
}

const unsigned Player::getGoalsScoredAllTime() const
{
	return goalsScoredAllTime;
}

const unsigned Player::getMatches() const
{
    return matchesPlayed;
}

const double Player::getSalary() const
{
	return salary;
}

const double Player::getTransferFee() const
{
	return transferFee;
}

void Player::setFirstName(const std::string& name)
{
	if (isValidName(name))
	{
		this->firstName = name;
	}
	else {
		this->firstName = "Unknown";
	}
}

void Player::setLastName(const std::string& name)
{
	if (isValidName(name))
	{
		this->lastName = name;
	}
	else {
		this->lastName = "Unknown";
	}
}

void Player::setNumber(const unsigned short number)
{
	if (number > 0 && number < 100)
	{
		this->number = number;
	}
	else {
		this->number = 21;
	}
}

void Player::setPosition(const Position position)
{
	if (position >= Position::Goalkeeper && position <= Position::Forward)
	{
		this->position = position;
	}
	else {
		this->position = Position::Unknown;
	}
}

void Player::setSalary(const double salary)
{
	if (salary > 0)
	{
		this->salary = salary;
	}
	else {
		this->salary = 100.0;
	}
}

void Player::setTransferFee(const double transferFee)
{
	if (transferFee > 0)
	{
		this->transferFee = transferFee;
	}
	else {
		this->transferFee = 100.0;
	}
}

void Player::setMatchesPlayed(const unsigned matches)
{
	if (matches >= 0)
	{
		this->matchesPlayed = matches;
	}
	else {
		this->matchesPlayed = 0;
	}
}

void Player::setGoalsScoredCurrently(const unsigned goals)
{
	if (goals >= 0)
	{
		this->goalsScoredCurrently = goals;
	}
	else {
		this->goalsScoredCurrently = 0;
	}
}

void Player::setGoalsScoredAllTime(const unsigned goals)
{
	if (goals >= goalsScoredCurrently)
	{
		this->goalsScoredAllTime = goals;
	}
	else {
		this->goalsScoredAllTime = goalsScoredCurrently;
	}
}

void Player::scoreGoal()
{
	goalsScoredCurrently++;
	goalsScoredAllTime++;
}

void Player::playMatch()
{
	matchesPlayed++;
}

void Player::adjustSalary(unsigned teamMatches)
{
	if (matchesPlayed > (teamMatches/2))
	{
		salary *= 1.2;
	}
	if (matchesPlayed < 7)
	{
		salary *= 0.9;
	}
	if (goalsScoredCurrently > 5)
	{
		salary *= 1.1;
	}
	if (goalsScoredCurrently > 10)
	{
		salary *= 1.2;
	}
	if (goalsScoredCurrently < 5 && position == Position::Forward)
	{
		salary *= 0.85;
	}

}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
	os << p.firstName << " " << p.lastName << " " << p.number << " " << (unsigned)p.position << " " << p.salary << " " << p.transferFee << " " << p.matchesPlayed << " " << p.goalsScoredCurrently << " " << p.goalsScoredAllTime;
	return os;
}

std::istream& operator>>(std::istream& is, Player& p)
{
	std::string firstName, lastName;
	unsigned short number;
	unsigned position, matchesPlayed, goalsScoredCurrently, goalsScoredAllTime;
	double salary, transferFee;

	is >> firstName >> lastName >> number >> position >> salary >> transferFee >> matchesPlayed >> goalsScoredCurrently >> goalsScoredAllTime;
	
	p.setFirstName(firstName);
	p.setLastName(lastName);
	p.setNumber(number);
	p.setPosition(static_cast<Position>(position));
	p.setSalary(salary);
	p.setTransferFee(transferFee);
	p.setMatchesPlayed(matchesPlayed);
	p.setGoalsScoredCurrently(goalsScoredCurrently);
	p.setGoalsScoredAllTime(goalsScoredAllTime);

	return is;
}



