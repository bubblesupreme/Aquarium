#include "Plankton.h"


Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_) :Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, 2, coefOfPlancton,&sprites.PlanktonMove)
{
	if ((radOfView > 4) || (radOfView < 2) ||
		(radOfDisp > 3) || (radOfDisp < 1) ||
		(lifeTime > 5) || (lifeTime < 3) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
	
}


Plankton::~Plankton()
{}

bool Plankton::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	body = &sprites.PlanktonMove;
	lifeTime--;
	reproduction++;
	if (lifeTime <= 0)
	{
		died(organisms);
		return true;
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = &sprites.PlanktonReprod;
			return false;
		}
	}
	body = &sprites.PlanktonMove;
	move(organisms, sizeAqua);
	return false;
}

bool Plankton::reproduce(std::vector<Organism*>& organisms)
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
		int chance = rand() % 2 + 5;
		while (chance)
		{
			organisms.push_back(new Plankton(location, rand() % 2 + 1, rand() % 2 + 2, rand() % 2 + 3));
			chance--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Plankton::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
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
							if ((u != this) && (radOfView >= way(u->getLocation())) && (u->getCoef() == coefOfHerbivore))
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
