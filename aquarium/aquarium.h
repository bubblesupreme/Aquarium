#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Plankton.h"
#include "Herbivore.h"
#include "Predator.h"

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::list<Organism*> organisms);
	~Aquarium();
	void show() const;
	void update();
	void addOrganism(Organism* org);
	std::list<Organism*> getListOfOrganisms() const;
	void randFill(int numOfHerbivore, int numOfPlanktones, int numOfPredators);
	bool isAlive() const;

private:
	bool isFull() const;
	coordinates size;
	std::list<Organism*> listOfOrganisms;
};

#endif
