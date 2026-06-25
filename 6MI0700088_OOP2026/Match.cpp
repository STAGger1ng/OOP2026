#include "Match.h"

Match::Match(Team* home, Team* away, unsigned short round, unsigned short totalRounds)
    : homeTeam(home), awayTeam(away),
    homeLineup(*home), awayLineup(*away),
    homeGoals(0), awayGoals(0),
    roundNumber(round), totalRounds(totalRounds)
{
}

void Match::selectLineup(Lineup& lineup, const std::string& teamName)
{
    std::cout << "Selecting lineup for " << teamName << " (add goalkeeper first):\n";
    unsigned short added = 0;
    while (added < 11)
    {
        std::string firstName, lastName;
        std::cout << "  Player " << (added + 1) << " - First name: ";
        std::cin >> firstName;
        std::cout << "  Player " << (added + 1) << " - Last name: ";
        std::cin >> lastName;

        if (lineup.addPlayer(firstName, lastName))
        {
            ++added;
        }
        else
        {
            std::cout << "  Cannot add " << firstName << " " << lastName
                << ". Player not found, already selected, or position limit reached. Try again.\n";
        }
    }
}

bool Match::selectLineups()
{
    bool lastThreeRounds = (totalRounds - roundNumber) < 3;
    if (roundNumber > (totalRounds * 2) / 3)
    {
        homeLineup.autoIncludeLowMatchPlayers(lastThreeRounds);
        awayLineup.autoIncludeLowMatchPlayers(lastThreeRounds);
    }

    selectLineup(homeLineup, homeTeam->getName());
    if (!homeLineup.isValidLineup())
    {
        std::cout << "Home team lineup is invalid. Match cannot start.\n";
        return false;
    }

    selectLineup(awayLineup, awayTeam->getName());
    if (!awayLineup.isValidLineup())
    {
        std::cout << "Away team lineup is invalid. Match cannot start.\n";
        return false;
    }

    return true;
}

void Match::enterResult()
{
    std::cout << "Enter goals for " << homeTeam->getName() << " (home): ";
    std::cin >> homeGoals;
    std::cout << "Enter goals for " << awayTeam->getName() << " (away): ";
    std::cin >> awayGoals;
}

void Match::addGoalScorer(unsigned short goalIndex)
{
    GoalScorer scorer;
    int teamChoice = 0;
    std::cout << "Goal " << goalIndex
        << " - Team (1 = " << homeTeam->getName()
        << ", 2 = " << awayTeam->getName() << "): ";
    std::cin >> teamChoice;
    scorer.isHomeTeam = (teamChoice == 1);

    std::cout << "  Scorer first name: ";
    std::cin >> scorer.firstName;
    std::cout << "  Scorer last name: ";
    std::cin >> scorer.lastName;

    scorers.push_back(scorer);
}

void Match::addGoals()
{
    unsigned short totalGoals = homeGoals + awayGoals;
    for (unsigned short i = 1; i <= totalGoals; ++i)
    {
        addGoalScorer(i);
    }
}

void Match::updateStats()
{
    homeTeam->updateAfterMatch(homeGoals, awayGoals);
    awayTeam->updateAfterMatch(awayGoals, homeGoals);

    homeLineup.updateStatsAfterMatch();
    awayLineup.updateStatsAfterMatch();

    for (const GoalScorer& scorer : scorers)
    {
        Team* team = scorer.isHomeTeam ? homeTeam : awayTeam;
        for (unsigned i = 0; i < team->getPlayers().size(); ++i)
        {
            Player* player = team->getPlayerAtIndex(i);
            if (player->getFirstName() == scorer.firstName &&
                player->getLastName() == scorer.lastName)
            {
                player->scoreGoal();
                break;
            }
        }
    }
}

void Match::play()
{
    if (!selectLineups())
    {
        return;
    }
    enterResult();
    addGoals();
    updateStats();
}

Team* Match::getHomeTeam() const
{
    return homeTeam;
}

Team* Match::getAwayTeam() const
{
    return awayTeam;
}

unsigned short Match::getHomeGoals() const
{
    return homeGoals;
}

unsigned short Match::getAwayGoals() const
{
    return awayGoals;
}

unsigned short Match::getRoundNumber() const
{
    return roundNumber;
}

const std::vector<GoalScorer>& Match::getScorers() const
{
    return scorers;
}

const Lineup& Match::getHomeLineup() const
{
    return homeLineup;
}

const Lineup& Match::getAwayLineup() const
{
    return awayLineup;
}
