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
		i->move(searchNeighbors(i,coefOfHerbivore),size);
	}
	for (auto i : this->listOfPlanktons)
	{
		i->life();
		i->move(searchNeighbors(i,coefOfPlancton),size);
	}
	for (auto i : this->listOfPredators)
	{
		i->life();
		i->move(searchNeighbors(i,coefOfPredator),size);
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
			int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
			if (result <= org->getRadOfView())
			{
				mapOfOrganism[*org] = result;
			}
		}
	}
	if ((coef == coefOfPlancton)||(coef==coefOfPredator))
	{
		for (auto u : listOfHerbivore)
		{
			coordinates posOfPredator = u->getLocation();
			int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
			if (result <= org->getRadOfView())
			{
				mapOfOrganism[*org] = result;
			}
		}
	}
	return mapOfOrganism;
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

bool Aquarium::produce()
{

}

bool Aquarium::eating()
{

}