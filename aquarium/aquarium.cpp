#include "aquarium.h"
#include <iostream>
#include <map>

Aquarium::Aquarium(std::pair<int, int> size) :size(size)
{
	map = new int*[size.first];
	for (int i = 0; i < size.first; i++)
	{
		map[i] = new int[size.second];
		for (int j = 0; j < size.second; j++)
			map[i][j] = 0;
	}

}
Aquarium::Aquarium(std::pair<int, int> size, std::vector<Fish*> listOfFishs,
	std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators)
{
	this->size = size;
	this->listOfFishs = listOfFishs;
	this->listOfPlanktons = listOfPlanktons;
	this->listOfPredators = listOfPredators;

	map = new int*[size.first];
	for (int i = 0; i < size.first; i++)
	{
		map[i] = new int[size.second];
		for (int j = 0; j < size.second; j++)
			map[i][j] = 0;
	}
}
Aquarium::~Aquarium()
{
	listOfFishs.clear();
	listOfPlanktons.clear();
	listOfPredators.clear();
}
void Aquarium::update()
{
	for (auto i : this->listOfFishs)
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

void  Aquarium::addFish(Fish* fish)
{
	listOfFishs.push_back(fish);
}
void  Aquarium::addPlankton(Plankton* plankton)
{
	listOfPlanktons.push_back(plankton);
}
void  Aquarium::addPredator(Predator* predator)
{
	listOfPredators.push_back(predator);
}
void Aquarium::show()
{
	std::cout << "F" << listOfFishs.size() << std::endl;
	std::cout << "Pl" << listOfPlanktons.size() << std::endl;
	std::cout << "Pr" << listOfPredators.size() << std::endl;
}
std::map<Organism&, int> Aquarium::searchNeighbors(Fish* fish)
{
	std::pair<int, int> pos = fish->getPosition();
	std::map<Organism&, int> mapOfPredators;
	for (auto u : listOfPredators)
		{
			std::pair<int, int> posOfPredator = u->getPosition();
			int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
			if (result <= fish->getRadOfView())
			{
				mapOfPredators[*fish] = result;
			}
		}
	return mapOfPredators;
}
std::map<Organism&, int> Aquarium::searchNeighbors(Plankton* plankton)
{
	std::pair<int, int> pos = plankton->getPosition();
	std::map<Organism&, int> mapOfPredators;
	for (auto u : listOfFishs)
	{
		std::pair<int, int> posOfPredator = u->getPosition();
		int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
		if (result <= plankton->getRadOfView_())
		{
			mapOfPredators[*plankton] = result;
		}
	}
	return mapOfPredators;
}
std::map<Organism&, int> Aquarium::searchNeighbors(Predator* predator)
{
	std::pair<int, int> pos = predator->getPosition();
	std::map<Organism&, int> mapOfFishs;
	for (auto u : listOfFishs)
	{
		std::pair<int, int> posOfPredator = u->getPosition();
		int result = wave(pos.second, pos.first, posOfPredator.second, posOfPredator.first, this->map, size.first, size.second);
		if (result <= predator->getRadOfView_())
		{
			mapOfFishs[*predator] = result;
		}
	}
	return mapOfFishs;

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
