#include "aquarium.h"
#include <iostream>
//#include <map>

Aquarium::Aquarium(coordinates size) :size(size)
{
	map = new int*[size.first];
	for (int i = 0; i < size.first; i++)
	{
		map[i] = new int[size.second];
		for (int j = 0; j < size.second; j++)
			map[i][j] = 0;
	}

}

Aquarium::Aquarium(coordinates size, std::vector<Herbivore*> listOfHerbivore,
	std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators)
	:size(size)
{
	this->listOfHerbivore = listOfHerbivore;
	this->listOfPlanktons = listOfPlanktons;
	this->listOfPredators = listOfPredators;

	map = new int*[size.first];
	for (int i = 0; i < size.first; i++)
	{
		map[i] = new int[size.second];
		for (int j = 0; j < size.second; j++)
			map[i][j] = 0;
	}
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
		if (i->getEatTime() / i->getStarvation() > 0.5)
		{

		}
		i->move(searchNeighbors(i));
	}
	for (auto i : this->listOfPlanktons)
	{
		i->life();
		i->move(searchNeighbors(i));
	}
	for (auto i : this->listOfPredators)
	{
		i->life();
		i->move(searchNeighbors(i));
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

std::map<Organism&, int> Aquarium::searchNeighbors(Herbivore* herbivore)
{
	coordinates pos = herbivore->getLocation();
	std::map<Organism&, int> mapOfPredators;
	for (auto u : listOfPredators)
	{
		coordinates posOfPredator = u->getLocation();
		int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
		if (result <= herbivore->getRadOfView())
		{
			mapOfPredators[*herbivore] = result;
		}
	}
	return mapOfPredators;
}

std::map<Organism&, int> Aquarium::searchNeighbors(Plankton* plankton)
{
	coordinates pos = plankton->getLocation();
	std::map<Organism&, int> mapOfHerbivore;
	for (auto u : listOfHerbivore)
	{
		coordinates posOfPredator = u->getLocation();
		int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
		if (result <= plankton->getRadOfView())
		{
			mapOfHerbivore[*plankton] = result;
		}
	}
	return mapOfHerbivore;
}

std::map<Organism&, int> Aquarium::searchNeighbors(Predator* predator)
{
	coordinates pos = predator->getLocation();
	std::map<Organism&, int> mapOfHerbivore;
	for (auto u : listOfHerbivore)
	{
		coordinates posOfPredator = u->getLocation();
		int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
		if (result <= predator->getRadOfView())
		{
			mapOfHerbivore[*predator] = result;
		}
	}
	return mapOfHerbivore;

}

int Aquarium::wave(int x, int y, int exX, int exY, int** map, int n, int m)
{
	bool fl = true;
	int temp = 2;
	map[x][y] = 2;
	while (map[exX][exY] == 0 && fl)
	{
		fl = false;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (map[i][j] == temp)
				{
					if (j > 0 && map[i][j - 1] == 0)
					{
						map[i][j - 1] = temp + 1;
						fl = true;
					}
					if (i > 0 && map[i - 1][j] == 0)
					{
						map[i - 1][j] = temp + 1;
						fl = true;
					}
					if (j < n - 1 && map[i][j + 1] == 0)
					{
						map[i][j + 1] = temp + 1;
						fl = true;
					}
					if (i < n - 1 && map[i + 1][j] == 0)
					{
						map[i + 1][j] = temp + 1;
						fl = true;
					}
				}
			}
		}
		temp++;
	}
	return temp;
}
