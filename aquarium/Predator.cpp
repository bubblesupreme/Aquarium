#include "Predator.h"



Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 3, coefOfPredator)
{
	if ((radOfView > 7) || (radOfView < 6) ||
		(radOfDisp > 7) || (radOfDisp < 6) ||
		(lifeTime > 5) || (lifeTime < 3) ||
		(eatTime > 3) || (eatTime < 2) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
}


Predator::~Predator()
{}

void Predator::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation == 0 || lifeTime == 0)
	{
		died(organisms);
		return;
	}
	if (eatTime / starvation > 0.5)
	{
		if (eat(organisms))
		{
			return;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			return;
		}
	}
	move(organisms, sizeAqua);
}

bool Predator::eat(std::vector<Organism*>& organisms)
{
	for (auto u : organisms)
	{
		if ((u->getCoef() == coefOfHerbivore) && (u != this))
		{
			if (radOfDisp >= way(u->getLocation()))
			{
				location = u->getLocation();
				starvation = eatTime;
				u->died(organisms);
				return true;
			}
		}
	}
	return false;
}

bool Predator::reproduce(std::vector<Organism*>& organisms)
{
	for (auto u : organisms)
	{
		if ((u != this) && (coef == u->getCoef()) && (radOfDisp >= way(u->getLocation())) &&
			(u->getReprodaction() > u->getPauseReprodaction()))
		{
			location = u->getLocation();
			reproduction = 0;
			u->reproductionUp();
			int chance = rand() % 1 + 1;
			while (chance)
			{
				organisms.push_back(&Predator(location, rand() % 1 + 6, rand() % 1 + 6, rand() % 2 + 3, rand() % 1 + 2));
				chance--;
			}
			return true;
		}
	}
	return false;
}

void Predator::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	if (organisms.size() == 1)
	{
		float minDist = sizeAqua.first*sizeAqua.second;
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
						if (distance < minDist)
						{
							minDist = distance;
							newLoc = coordinates(location.first + i, location.second + j);
						}
					}
				}
			}

			location = newLoc;
		}
	}
	else
	{
		int newx = rand() % radOfDisp;
		if (newx > sizeAqua.first)
		{
			newx = sizeAqua.first;
		}
		int newy = rand() % radOfDisp;
		if (newy > sizeAqua.second)
		{
			newy = sizeAqua.second;
		}
		location = coordinates(location.first + newx, location.second + newy);
	}

}