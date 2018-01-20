#include "Predator.h"



Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 2, coefOfPredator, &sprites.PredatorMove)
{
	if ((radOfView > 10) || (radOfView < 6) ||
		(radOfDisp > 7) || (radOfDisp < 6) ||
		(lifeTime > 5) || (lifeTime < 4) ||
		(eatTime > 3) || (eatTime < 2) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
}


Predator::~Predator()
{}

bool Predator::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	body = &sprites.PredatorMove;
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation == 0 || lifeTime == 0)
	{
		died(organisms);
		return  true;
	}
	if (eatTime / starvation > 0.5)
	{
		if (eat(organisms))
		{
			body = &sprites.PredatorEat;
			return false;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = &sprites.PredatorReprod;
			return false;
		}
	}
	body = &sprites.PredatorMove;
	move(organisms, sizeAqua);
	return false;
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
			int chance = rand() % 1 + 2;
			while (chance)
			{
				organisms.push_back(new Predator(location, rand() % 1 + 6, rand() % 4 + 6, rand() % 1 + 4, rand() % 1 + 2));
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