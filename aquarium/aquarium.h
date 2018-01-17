#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Herbivore.h"
#include "Plankton.h"
#include "Predator.h"
#include <vector>

/*
Coefficient of Plancton 1
Coefficient of Herbivore 3
Coefficient of Predator 4
*/

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::vector<Herbivore*> listOfHerbivore,
		std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators);
	~Aquarium();
	void show();
	void update();
	void addHerbivore(Herbivore* herbivore);
	void addPlankton(Plankton* plankton);
	void addPredator(Predator* predator);


private:
	bool produce(Organism*, int coef);
	bool eating(Organism*, int coef);
	std::map<Organism&, int> searchNeighbors(Organism*, int coef);
	int way(int x1, int y1, int x2, int y2);
	const std::pair<int, int> size;
	std::vector<Herbivore*> listOfHerbivore;
	std::vector<Plankton*> listOfPlanktons;
	std::vector<Predator*> listOfPredators;
	const int coefOfPlancton = 1;
	const int coefOfHerbivore = 3;
	const int coefOfPredator = 4;
};

#endif
