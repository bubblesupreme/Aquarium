#include "aquarium.h"
#include <cstdlib>
#include "Plankton.h"
Aquarium::Aquarium(coordinates size) :size(size){}

Aquarium::Aquarium(coordinates size, std::vector<Organism*> org)
	:size(size)
{
	this->listOfOrganisms = org;
	int sum = 0;
	for (auto i : org)
	{
		sum += i->getCoef();
		if (sum > size.first*size.second)
		{
			throw Exception(4);
		}
	}
}

Aquarium::~Aquarium()
{
	listOfOrganisms.~vector();
}

void Aquarium::update()
{
	
	for (auto i=1; i< listOfOrganisms.size();i)
	{
//		i->move(listOfOrganisms, size);
		if (!(listOfOrganisms[i]->update(listOfOrganisms, size)))
			i++;
		//i->update(size);
		//i->test();
		std::cout << "   !" << listOfOrganisms.size() << std::endl;
	}
}

void  Aquarium::addOrganism(Organism* organism)
{
	int sum = organism->getCoef();
	for (auto i : listOfOrganisms)
	{
		sum += i->getCoef();
		if (sum > size.first*size.second)
		{
			throw Exception(4);
		}
	}

	listOfOrganisms.push_back(organism);
	
}

void Aquarium::show()
{
	int fish = 0;
	int plank = 0;
	int pred = 0;
	for (auto i : listOfOrganisms)
	{
		if (i->getCoef() == coefOfHerbivore)
		{
			fish += 1;
		}
		else if (i->getCoef() == coefOfPlancton)
		{
			plank += 1;
		}
		else
		{
			pred += 1;
		}
	}
	std::cout << "\nF" << fish << std::endl;
	std::cout << "Pl" << plank << std::endl;
	std::cout << "Pr" << pred << std::endl;
}

std::vector<Organism*> Aquarium::getListOfOrganisms()
{ 
	return listOfOrganisms; 
}

