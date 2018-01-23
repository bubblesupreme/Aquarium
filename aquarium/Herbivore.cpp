#include "Herbivore.h"



Herbivore::Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 4, coefOfHerbivore,&sprites.HerbivoreMove)
{
	if ((radOfView > 8) || (radOfView < 6) ||
		(radOfDisp > 6) || (radOfDisp < 4) ||
		(lifeTime > 11) || (lifeTime < 8) ||
		(eatTime > 5) || (eatTime < 4) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
}


Herbivore::~Herbivore()
{}

bool Herbivore::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	body = &sprites.HerbivoreMove;
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation <= 0 || lifeTime <= 0)
	{
		died(organisms);
		return true;
	}
	if (eatTime / starvation > 0.5)
	{
		if (eat(organisms))
		{
			body = &sprites.HerbivoreEat;
			return false;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = &sprites.HerbivoreReprod;
			return false;
		}
	}
	body = &sprites.HerbivoreMove;
	move(organisms, sizeAqua);
	return false;
}

bool Herbivore::eat(std::vector<Organism*>& organisms)
{
	std::vector<Organism*> neighbors;

	for (auto u : organisms)
	{
		if ((u->getCoef() == coefOfPlancton) && (u != this))
		{
			if (radOfDisp >= way(u->getLocation()))
			{
				neighbors.push_back(u);
			}
		}
	}
	if (neighbors.size() > 0)
	{
		int choice = rand() % neighbors.size();
		location = neighbors[choice]->getLocation();
		starvation = eatTime;
		neighbors[choice]->died(organisms);
		return true;
	}
	else
	{
		return false;
	}
}

bool Herbivore::reproduce(std::vector<Organism*>& organisms)
{
	std::vector<Organism*> neighbors;

	for (auto u : organisms)
	{
		if ((u != this) && (coef == u->getCoef()) && (radOfDisp >= way(u->getLocation())) &&
			(u->getReprodaction() > u->getPauseReprodaction()))
		{
			neighbors.push_back(u);
		}
	}
	if (neighbors.size() > 0)
	{
		int choice = rand() % neighbors.size();
		location = neighbors[choice]->getLocation();
		reproduction = 0;
		neighbors[choice]->reproductionUp();
		int chance = rand() % 3 + 2;
		while (chance)
		{
			organisms.push_back(new Herbivore(location, rand() % 2 + 4, rand() % 2 + 6, rand() % 3 + 8, rand() % 1 + 4));
			chance--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Herbivore::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	float maxDist = 0;
	if (organisms.size() != 1)
	{
		
		coordinates newLoc(location.first, location.second);
		for (int i = (-1)*radOfDisp; i <= radOfDisp; i++)
		{
			if ((location.first + i <= sizeAqua.first) && (location.first + i >= 0))
			{
				for (int j = (-1)*radOfDisp; j <= radOfDisp; j++)
				{
					if ((location.second + j <= sizeAqua.second) && (location.second + j >= 0))
					{
						int distance = 0;
						for (auto u : organisms)
						{
							if ((u != this) && (radOfView >= way(u->getLocation())) && (u->getCoef() == coefOfPredator))
							{
								distance += way(u->getLocation());
							}
						}
						if (distance > maxDist)
						{
							maxDist = distance;
							newLoc = coordinates(location.first + i, location.second + j);
						}
					}
				}
			}

			location = newLoc;
		}
	}
	if ((organisms.size() == 1) || (maxDist == 0))
	{
		int newx = rand() % radOfDisp - radOfDisp;
		if (location.first + newx > sizeAqua.first)
		{
			newx = sizeAqua.first - location.first;
		}
		if (location.first + newx <0)
		{
			newx = 0 - location.first;
		}
		int newy = rand() % radOfDisp - radOfDisp;
		if (location.second + newy > sizeAqua.second)
		{
			newy = sizeAqua.second - location.second;
		}
		if (location.second + newy <0)
		{
			newy = 0 - location.second;
		}
		location = coordinates(location.first + newx, location.second + newy);
	}

}