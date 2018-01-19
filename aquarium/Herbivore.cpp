#include "Herbivore.h"



Herbivore::Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 3, coefOfHerbivore,HerbivoreMove)
{
	if ((radOfView > 9) || (radOfView < 6) ||
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

void Herbivore::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
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
			body = HerbivoreEat;
			return;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = HerbivoreReprod;
			return;
		}
	}
	body = HerbivoreMove;
	move(organisms, sizeAqua);
}

bool Herbivore::eat(std::vector<Organism*>& organisms)
{
	for (auto u : organisms)
	{
		if ((u->getCoef() == coefOfPlancton) && (u != this))
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

bool Herbivore::reproduce(std::vector<Organism*>& organisms)
{
	for (auto u : organisms)
	{
		if ((u != this) && (coef == u->getCoef()) && (radOfDisp >= way(u->getLocation())) &&
			(u->getReprodaction() > u->getPauseReprodaction()))
		{
			location = u->getLocation();
			reproduction = 0;
			u->reproductionUp();
			int chance = rand() % 2 + 2;
			while (chance)
			{
				organisms.push_back(&Herbivore(location, rand() % 2 + 4, rand() % 3 + 6, rand() % 3 + 8, rand() % 1 + 4));
				chance--;
			}
			return true;
		}
	}
	return false;
}

void Herbivore::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	if (organisms.size() == 1)
	{
		float maxDist = sizeAqua.first*sizeAqua.second;
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