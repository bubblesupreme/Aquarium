#include "aquarium.h"
#include <iostream>
#include <cstdlib>

Aquarium::Aquarium(coordinates size) :size(size){}

Aquarium::Aquarium(coordinates size, std::vector<Herbivore*> listOfHerbivore,
	std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators)
	:size(size)
{
	this->listOfHerbivore = listOfHerbivore;
	this->listOfPlanktons = listOfPlanktons;
	this->listOfPredators = listOfPredators;

	if ((listOfHerbivore.size()*coefOfHerbivore
		+listOfPlanktons.size()*coefOfPlancton
		+listOfPredators.size()*coefOfPredator)
		>size.first*size.second)
	{
		throw Exception(4);
	}
}

Aquarium::~Aquarium()
{
	listOfHerbivore.clear();
	listOfPlanktons.clear();
	listOfPredators.clear();
}

void Aquarium::update()
{
	for (auto i : this->listOfHerbivore)
	{

		i->life();
		i->hunger();
		if (i->getStarvation() == 0 || i->getLifeTime() == 0)
		{
			std::swap(i, listOfHerbivore.back());
			listOfHerbivore.pop_back();
			continue;
		}
		if (i->getEatTime() / i->getStarvation() > 0.5)
		{
			if (eating(i, coefOfHerbivore))
			{
				i->eat();
			}

		}
		else if (i->getReprodaction() >= i->getPauseReprodaction())
		{
			if(produce(i, coefOfHerbivore))
			{
				i->reproduce();
			}
			
		}
		else
		{
			i->move(searchNeighbors(i, coefOfHerbivore), size);
		}

	}
	for (auto i : this->listOfPlanktons)
	{
		i->life();
		i->move(searchNeighbors(i, coefOfPlancton), size);

		for (auto i : this->listOfPredators)
		{
			i->life();
			i->hunger();
			if (i->getStarvation() == 0 || i->getLifeTime() == 0)
			{
				std::swap(i, listOfPredators.back());
				listOfPredators.pop_back();
				continue;
			}
			if (i->getEatTime() / i->getStarvation() > 0.5)
			{
				if (eating(i, coefOfPredator))
				{
					i->eat();
				}

			}
			else if (i->getReprodaction() >= i->getPauseReprodaction())
			{
				if(produce(i, coefOfPredator))
				{
					i->reproduce();
				}
				
			}
			else
			{
				i->move(searchNeighbors(i, coefOfPredator), size);
			}


		}
	}
}
void  Aquarium::addHerbivore(Herbivore* herbivore)
{
	if (((listOfHerbivore.size()+1)*coefOfHerbivore
		+ listOfPlanktons.size()*coefOfPlancton
		+ listOfPredators.size()*coefOfPredator)
		>size.first*size.second)
	{
		throw Exception(4);
	}
	else
	{
		listOfHerbivore.push_back(herbivore);
	}
}

void  Aquarium::addPlankton(Plankton* plankton)
{
	if ((listOfHerbivore.size()*coefOfHerbivore
		+ (listOfPlanktons.size()+1)*coefOfPlancton
		+ listOfPredators.size()*coefOfPredator)
	>size.first*size.second)
	{
		throw Exception(4);
	}
	else
	{
		listOfPlanktons.push_back(plankton);
	}
}

void  Aquarium::addPredator(Predator* predator)
{
	if ((listOfHerbivore.size()*coefOfHerbivore
		+ listOfPlanktons.size()*coefOfPlancton
		+ (listOfPredators.size()+1)*coefOfPredator)
		>size.first*size.second)
	{
		throw Exception(4);
	}
	else
	{
		listOfPredators.push_back(predator);
	}
}

void Aquarium::show()
{
	std::cout << "F" << listOfHerbivore.size() << std::endl;
	std::cout << "Pl" << listOfPlanktons.size() << std::endl;
	std::cout << "Pr" << listOfPredators.size() << std::endl;
}

std::map<Organism&, int> Aquarium::searchNeighbors(Organism* org, int coef)
{
	coordinates pos = org->getLocation();
	std::map<Organism&, int> mapOfOrganism;
	if (coef == coefOfHerbivore)
	{
		for (auto u : listOfPredators)
		{
			coordinates posOfPredator = u->getLocation();
			int result = way(pos.second, pos.first, posOfPredator.second, posOfPredator.first);
			if (result <= org->getRadOfView())
			{
				mapOfOrganism[*u] = result;
			}
		}
	}
	if ((coef == coefOfPlancton)||(coef==coefOfPredator))
	{
		for (auto u : listOfHerbivore)
		{
			coordinates posOfPredator = u->getLocation();
			int result = way(pos.second, pos.first, posOfPredator.second, posOfPredator.first);
			if (result <= org->getRadOfView())
			{
				mapOfOrganism[*u] = result;
			}
		}
	}
	return mapOfOrganism;
}

int Aquarium::way(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

bool Aquarium::produce(Organism* org, int coef)
{
	coordinates pos = org->getLocation();
	if (coef == coefOfHerbivore)
	{
		for (auto u : listOfHerbivore)
		{
			coordinates posOfHerbivore = u->getLocation();
			int result = way(pos.second, pos.first, posOfHerbivore.second, posOfHerbivore.first);
			if ((result <= org->getRadOfDisp()) && (u->getReprodaction() >= u->getPauseReprodaction()))
			{
				int chance = rand() % 3 + 3;
				while (chance)
				{
					int radOfView = rand() % 3 + 6;
					int radOfDisp = rand() % 2 + 4;
					int lifeTime = rand() % 3 + 8;
					int eattime = rand() % 1 + 4;
					int location = rand() % 4 + 1;
					posOfHerbivore.first += location;
					posOfHerbivore.second += location;
					listOfHerbivore.push_back(&Herbivore(posOfHerbivore, radOfDisp, radOfView, lifeTime, eattime));
					chance--;
				}
				u->reproduce();
				org->moveDisl(u->getLocation());
				return true;
			}
		}
	}
	else if (coef == coefOfPredator)
	{
		for (auto u : listOfPredators)
		{
			coordinates posOfPredator = u->getLocation();
			int result = way(pos.second, pos.first, posOfPredator.second, posOfPredator.first);
			if ((result <= org->getRadOfDisp()) && (u->getReprodaction() >= u->getPauseReprodaction()))
			{
				int chance = rand() % 2 + 1;
				while (chance)
				{
					int radOfView = rand() % 3 + 6;
					int radOfDisp = rand() % 2 + 4;
					int lifeTime = rand() % 3 + 8;
					int eattime = rand() % 1 + 4;
					int location = rand() % 4 + 1;
					posOfPredator.first += location;
					posOfPredator.second += location;
					listOfPredators.push_back(&Predator(posOfPredator, radOfDisp, radOfView, lifeTime, eattime));
					chance--;
				}
				u->reproduce();
				org->moveDisl(u->getLocation());
				return true;
			}
		}
	}
	else
	{
		for (auto u : listOfPlanktons)
		{
			coordinates posOfPlanktons = u->getLocation();
			int result = way(pos.second, pos.first, posOfPlanktons.second, posOfPlanktons.first);
			if ((result <= org->getRadOfDisp()) && (u->getReprodaction() >= u->getPauseReprodaction()))
			{
				int chance = rand() % 2 + 1;
				while (chance)
				{
					int radOfView = rand() % 3 + 6;
					int radOfDisp = rand() % 2 + 4;
					int lifeTime = rand() % 3 + 8;
					int location = rand() % 4 + 1;
					posOfPlanktons.first += location;
					posOfPlanktons.second += location;
					listOfPlanktons.push_back(&Plankton(posOfPlanktons, radOfDisp, radOfView, lifeTime));
					chance--;
				}
				u->reproduce();
				org->moveDisl(u->getLocation());
				return true;
			}
		}
	}
	return false;
}

bool Aquarium::eating(Organism* org, int coef)
{
	coordinates pos = org->getLocation();
	if (coef == coefOfHerbivore)
	{
		for (auto u : listOfPlanktons)
		{
			coordinates posOfPlankton = u->getLocation();
			int result = way(pos.second, pos.first, posOfPlankton.second, posOfPlankton.first);
			if (result <= org->getRadOfDisp())
			{
				std::swap(u, listOfPlanktons.back());
				listOfPlanktons.pop_back();
				org->moveDisl(u->getLocation());
				return true;
			}
		}
	}
	else if (coef == coefOfPredator)
	{
		for (auto u : listOfHerbivore)
		{
			coordinates posOfPredator = u->getLocation();
			int result = way(pos.second, pos.first, posOfPredator.second, posOfPredator.first);
			if (result <= org->getRadOfDisp())
			{
				std::swap(u, listOfHerbivore.back());
				listOfHerbivore.pop_back();
				org->moveDisl(u->getLocation());
				return true;
			}
		}
	}
	return false;
}
