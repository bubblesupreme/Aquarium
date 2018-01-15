#pragma once
#include "Fish.h"
#include "Plankton.h"
#include "Predator.h"
#include <vector>

///
class Aquarium
{
public:
	Aquarium(std::pair<int, int> size);
	Aquarium(std::pair<int, int> size, std::vector<Fish*> listOfFishs,
		std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators);
	~Aquarium();
	void show();
	void update();
	void addFish(Fish* fish);
	void addPlankton(Plankton* plankton);
	void addPredator(Predator* predator);


private:
	int wave(int x, int y, int exX, int exY, int** map, int n, int m);
	std::pair<int, int> size;
	int** map;
	std::vector<Fish*> listOfFishs;
	std::vector<Plankton*> listOfPlanktons;
	std::vector<Predator*> listOfPredators;
	void reprodaction();
	void eating();
	std::map<Organism&, int> searchNeighbors(Fish*);
	std::map<Organism&, int> searchNeighbors(Plankton*);
	std::map<Organism&, int> searchNeighbors(Predator*);

};


