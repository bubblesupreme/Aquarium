#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Herbivore.h"
#include "Plankton.h"
#include "Predator.h"
#include <vector>

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::vector<Organism*> org);
	~Aquarium();
	void show();
	void update();
	void addOrganism(Organism* org);
private:
	coordinates size;
	std::vector<Organism*> listOfOrganisms;
	const int coefOfPlancton = 1;
	const int coefOfHerbivore = 3;
	const int coefOfPredator = 4;
};

#endif

