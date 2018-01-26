#include "Plankton.h"


Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, Sprites* sprites_) :Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, 4, coefOfPlancton,sprites_)
{
	if ((radOfView > 4) || (radOfView < 2) ||
		(radOfDisp > 3) || (radOfDisp < 1) ||
		(lifeTime > 10) || (lifeTime < 5) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
	
}


Plankton::~Plankton()
{}

void Plankton::update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del)
{
	body = sprites->PlanktonMove;
	lifeTime--;
	reproduction++;
	if (lifeTime <= 0)
	{
		//died(organisms);
		del.insert(this);
		return;
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = sprites->PlanktonReprod;
		}
		return;
	}
	body = sprites->PlanktonMove;
	move(organisms, sizeAqua);
}

bool Plankton::reproduce(std::list<Organism*>& organisms)
{
	std::list<Organism*>::iterator  choice = organisms.end();
	int minWay=10000;
	for (auto u = organisms.begin(); u != organisms.end(); u++)
	{
		if ((*u != this) && (coef == (*u)->getCoef()) && (radOfDisp >= way((*u)->getLocation())) &&
			((*u)->getReprodaction() > (*u)->getPauseReprodaction()))
		{
			if (way((*u)->getLocation()) < minWay)
			{
				minWay = way((*u)->getLocation());
				choice = u;
			}
		}
	}
	if (choice!= organisms.end())
	{
		location = (*choice)->getLocation();
		reproduction = 0;
		(*choice)->reproductionUp();
		int chance = rand() % 5 + 5;
		while (chance)
		{
			organisms.push_back(new Plankton(location, rand() % 2 + 1, rand() % 2 + 2, rand() % 5 + 5, sprites));
			chance--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Plankton::move(std::list<Organism*>& organisms, coordinates sizeAqua)
{
	float maxDist = 0;

	std::list<Organism*> neighbors;
	if (organisms.size() != 1)
	{
		for (auto u : organisms)
		{
			if ((u != this) && (radOfView >= way(u->getLocation())) && (u->getCoef() == coefOfHerbivore))
			{
				neighbors.push_back(u);
			}
		}

		coordinates newLoc(location.first, location.second, location.third);
		for (int i = (-1)*radOfDisp; i <= radOfDisp; i++)
		{
			if ((location.first + i <= sizeAqua.first) && (location.first + i >= 0))
			{
				for (int j = (-1)*radOfDisp; j <= radOfDisp; j++)
				{
					if ((location.second + j <= sizeAqua.second) && (location.second + j >= 0))
					{
						for (int h = (-1)*radOfDisp; h <= radOfDisp; h++)
						{
							if ((location.third + h <= sizeAqua.third) && (location.third + h >= 0))
							{
								int distance = 0;
								for (auto u : neighbors)
								{
									distance += way(coordinates(location.first + i, location.second + j,
										location.third + h), u->getLocation());
								}
								if (distance > maxDist)
								{
									maxDist = distance;
									newLoc = coordinates(location.first + i, location.second + j, location.third + h);
								}
							}
						}
					}
				}
			}

			location = newLoc;
		}
	}
	if ((organisms.size() == 1) || (maxDist == 0))
	{
		int newx = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.first + newx > sizeAqua.first)
		{
			newx = sizeAqua.first - location.first;
		}
		if (location.first + newx < 0)
		{
			newx = 0 - location.first;
		}
		int newy = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.second + newy > sizeAqua.second)
		{
			newy = sizeAqua.second - location.second;
		}
		if (location.second + newy < 0)
		{
			newy = 0 - location.second;
		}
		int newz = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.third + newz > sizeAqua.third)
		{
			newz = sizeAqua.third - location.third;
		}
		if (location.third + newz < 0)
		{
			newz = 0 - location.third;
		}
		location = coordinates(location.first + newx, location.second + newy, location.third + newz);
	}

}
