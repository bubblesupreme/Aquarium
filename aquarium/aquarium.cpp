#include "aquarium.h"
#include <iostream>

Aquarium::Aquarium(coordinates size) :size(size){}

Aquarium::Aquarium(coordinates size, std::list<Organism*> organisms)
	:size(size)
{
	this->listOfOrganisms = organisms;
	int sum = 0;
	for (auto org : organisms)
	{
		sum += org->getCoef();
		if (sum > size.first*size.second*size.third)
		{
			throw Exception(4);
		}
	}
}

void Aquarium::randFill(int numOfHerbivore, int numOfPlanktones,int numOfPredators)
{
	Sprites* sprites = new Sprites;
	int chance = numOfPlanktones;
	while (chance)
	{
		coordinates posOfPlankton;
		int radOfView = rand() % radOfViewPlanktonDelta + radOfViewPlankton;
		int radOfDisp = rand() % radOfDispPlanktonDelta + radOfDispPlankton;
		int lifeTime = rand() % lifeTimePlanktonDelta + lifeTimePlankton;
		posOfPlankton.first = rand() % (int)size.first ;
		posOfPlankton.second = rand() % (int)size.second ;
		posOfPlankton.third = rand() % (int)size.third;
		bool sex = rand() % 2;
		try
		{
			listOfOrganisms.push_back(new Plankton(posOfPlankton, radOfDisp, radOfView, lifeTime,sex, sprites));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}

	chance = numOfHerbivore;
	while (chance)
	{
		coordinates posOfHerbivore;
		int radOfView = rand() % radOfViewHerbivoreDelta + radOfViewHerbivore;
		int radOfDisp = rand() % radOfDispHerbivoreDelta + radOfDispHerbivore;
		int lifeTime = rand() % lifeTimeHerbivoreDelta + lifeTimeHerbivore;
		int eattime = rand() % eatTimeHerbivoreDelta + eatTimeHerbivore;
		posOfHerbivore.first = rand() % (int)size.first;
		posOfHerbivore.second = rand() % (int)size.second;
		posOfHerbivore.third = rand() % (int)size.third;
		bool sex = rand() % 2;
		try
		{
			listOfOrganisms.push_back(new Herbivore(posOfHerbivore, radOfDisp, radOfView, lifeTime, eattime,sex, sprites));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}

	chance = numOfPredators;
	while (chance)
	{
		coordinates posOfPredators;
		int radOfView = rand() % radOfViewPredatorDelta + radOfViewPredator;
		int radOfDisp = rand() % radOfDispPredatorDelta + radOfDispPredator;
		int lifeTime = rand() % lifeTimePredatorDelta + lifeTimePredator;
		int eattime = rand() % eatTimePredatorDelta + eatTimePredator;
		posOfPredators.first = rand() % (int)size.first;
		posOfPredators.second = rand() % (int)size.second;
		posOfPredators.third = rand() % (int)size.third ;
		bool sex = rand() % 2;
		try
		{
			listOfOrganisms.push_back(new Predator(posOfPredators, radOfDisp, radOfView, lifeTime, eattime,sex, sprites));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}
}

Aquarium::~Aquarium()
{}

void Aquarium::update()
{
	int fish = 0;
	int plank = 0;
	int pred = 0;
	std::set<Organism*> del;
	for (auto org :listOfOrganisms)
	{
		org->update(listOfOrganisms, coordinates(size.first - 1, size.second - 1, size.third - 1),del);
		//std::cout << (*org)->getLocation().first*35 << "-" << (*org)->getLocation().second* 35 << "  ";
		if (org->getCoef() == coefOfHerbivore)
		{
			fish += 1;
		}
		else if (org->getCoef() == coefOfPlancton)
		{
			plank += 1;
		}
		else
		{
			pred += 1;
		}
	}
	for (auto org = listOfOrganisms.begin(); org != listOfOrganisms.end();)
	{

		if (del.find(*org) != del.end())
		{
			
			org =listOfOrganisms.erase(org++);
		}
		else
		{
			org++;
		}
	}
	std::cout << "\nF" << fish << std::endl;
	std::cout << "Pl" << plank << std::endl;
	std::cout << "Pr" << pred << std::endl;
}

void  Aquarium::addOrganism(Organism* organism)
{
	int sum = organism->getCoef();
	for (auto org : listOfOrganisms)
	{
		sum += org->getCoef();
		if (sum > size.first*size.second)
		{
			throw Exception(4);
		}
	}
	listOfOrganisms.push_back(organism);
}

void Aquarium::isAlive() const
{	
	int fish = 0;
	int plank = 0;
	int pred = 0;
	int sum = 0;
	for (auto org : listOfOrganisms)
	{
		if (org->getCoef() == coefOfHerbivore)
		{
			fish += 1;
		}
		else if (org->getCoef() == coefOfPlancton)
		{
			plank += 1;
		}
		else
		{
			pred += 1;
		}
		sum += org->getCoef();
	}
	if (fish == 0 || plank == 0 || pred == 0)
	{
		std::cout << fish << "fish/" << plank << "plank/pred" << pred << std::endl;
		throw Exception(2);
	}
	if (sum > size.first*size.second*size.third)
	{
		throw Exception(3);
	}
}

void Aquarium::show() const
{
	int fish = 0;
	int plank = 0;
	int pred = 0;
	std::cout << "   !" << listOfOrganisms.size() << std::endl;
	for (auto org : listOfOrganisms)
	{
		if (org->getCoef() == coefOfHerbivore)
		{
			fish += 1;
		}
		else if (org->getCoef() == coefOfPlancton)
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

std::list<Organism*> Aquarium::getListOfOrganisms() const
{ 
	return listOfOrganisms; 
}
