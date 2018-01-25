#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Organism.h"
#include "Constants.h"

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::list<Organism*> org);
	~Aquarium();
	void show();
	void update();
	void addOrganism(Organism* org);
	std::list<Organism*> getListOfOrganisms();
	bool isAlive();

private:
	bool isFull();
	coordinates size;
	std::list<Organism*> listOfOrganisms;
};

#endif
