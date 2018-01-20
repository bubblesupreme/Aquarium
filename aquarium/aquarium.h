#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Organism.h"
#include "Constants.h"

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::vector<Organism*> org);
	~Aquarium();
	void show();
	void update();
	void addOrganism(Organism* org);
	std::vector<Organism*> getListOfOrganisms();
private:
	coordinates size;
	std::vector<Organism*> listOfOrganisms;
};

#endif
