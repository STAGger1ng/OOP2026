#pragma once

#include "Championship.h"

class ChampionshipCollection
{
private:
	std::vector<Championship> championships;

public:
    void addChampionship(const Championship& championship);
    void createNewSeason();
    Championship* findByYear(int year);

    void saveAll(std::ofstream& out);
    void loadAll(std::ifstream& in);

    void printHistory() const;
};

