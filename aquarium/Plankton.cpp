#include "Plankton.h"


Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_) :Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, 2, 1)
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

void Plankton::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	lifeTime--;
	reproduction++;
	if (lifeTime == 0)
	{
		died(organisms);
		return;
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

bool Plankton::reproduce(std::vector<Organism*>& organisms)
{
	for (auto u : organisms)
	{
		if ((u != this) && (coef == u->getCoef()) && (radOfDisp >= way(u->getLocation())) &&
			(u->getReprodaction() > u->getPauseReprodaction()))
		{
			location = u->getLocation();
			reproduction = 0;
			u->reproductionUp();
			int chance = rand() % 2 + 3;
			while (chance)
			{
				organisms.push_back(&Plankton(location, rand() % 2 + 1, rand() % 2 + 2, rand() % 5 + 3));
				chance--;
			}
			return true;
		}
	}
	return false;
}

void Plankton::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
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
