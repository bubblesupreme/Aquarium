#include "aquarium.h"



Aquarium::Aquarium(std::pair<double, double> size, std::vector<Fish*> listOfFishs,
	std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators)
{
	this->size = size;
	this->listOfFishs = listOfFishs;
	this->listOfPlanktons = listOfPlanktons;
	this->listOfPredators = listOfPredators;
}
Aquarium::~Aquarium()
{
	
	for (auto i : this->listOfFishs)
	{
		delete i;
	}
	for (auto i : this->listOfPlanktons)
	{
		delete i;
	}
	for (auto i : this->listOfPredators)
	{
		delete i;
	}
}
void Aquarium::update()
{
	for (auto i : this->listOfFishs)
	{
		i->update();
	}
	for (auto i : this->listOfPlanktons)
	{
		i->update();
	}
	for (auto i : this->listOfPredators)
	{
		i->update();
	}
}
