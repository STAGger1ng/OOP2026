#include "ChampionshipCollection.h"

void ChampionshipCollection::addChampionship(const Championship& championship)
{
    championships.push_back(championship);
}

void ChampionshipCollection::createNewSeason()
{

}

Championship* ChampionshipCollection::findByYear(int year)
{
    for (int i = 0; i < championships.size(); i++)
    {
        if (championships[i].getYear() == year)
        {
            return &championships[i];
        }
    }
    return nullptr;
}

void ChampionshipCollection::saveAll(std::ofstream& out)
{
    for (int i = 0; i < championships.size(); i++)
    {
        championships[i].save(out);
    }
}

void ChampionshipCollection::loadAll(std::ifstream& in)
{
    for (int i = 0; i < championships.size(); i++)
    {
        championships[i].load(in);
    }
}

void ChampionshipCollection::printHistory() const
{
    for (int i = 0; i < championships.size(); i++)
    {
        championships[i].printTable();
    }
}
