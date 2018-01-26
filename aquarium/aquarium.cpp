#include "aquarium.h"
#include <cstdlib>


Aquarium::Aquarium(coordinates size) :size(size){}

Aquarium::Aquarium(coordinates size, std::list<Organism*> org)
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
	listOfOrganisms.~list();
}

void Aquarium::update()
{
	std::set<Organism*> del;
	for (auto it=listOfOrganisms.begin();it!=listOfOrganisms.end();it++)
	{
		(*it)->update(listOfOrganisms, coordinates(size.first - 1, size.second - 1, size.third - 1),del);
		isFull();
	}
	for (auto it = listOfOrganisms.begin(); it != listOfOrganisms.end();)
	{
		if (del.find(*it) != del.end())
		{
			it=listOfOrganisms.erase(it++);
		}
		else
		{
			it++;
		}
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
bool Aquarium::isAlive()
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
	if (fish == 0 || plank == 0 || pred == 0)
	{
		std::cout << fish << "fish/" << plank << "plank/pred" << pred << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}
void Aquarium::show()
{
	int fish = 0;
	int plank = 0;
	int pred = 0;
	std::cout << "   !" << listOfOrganisms.size() << std::endl;
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

std::list<Organism*> Aquarium::getListOfOrganisms()
{ 
	return listOfOrganisms; 
}
bool Aquarium::isFull()
{
	int sum = 0;
	for (auto i : listOfOrganisms)
	{
		sum += i->getCoef();
		if (sum > size.first*size.second*size.third)
		{
			throw Exception(4);
		}
	}
	return false;
}
