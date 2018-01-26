#include "Predator.h"



Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_, Sprites* sprites_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 6, coefOfPredator, sprites_)
{
	if ((radOfView > 10) || (radOfView < 6) ||
		(radOfDisp > 7) || (radOfDisp < 6) ||
		(lifeTime > 20) || (lifeTime < 15) ||
		(eatTime > 7) || (eatTime < 4) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}

}


Predator::~Predator()
{}

void Predator::update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del)
{
	body = sprites->PredatorMove;
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation == 0 || lifeTime <= 0)
	{
		//died(organisms);
		del.insert(this);
		return;
	}
	if (eatTime / starvation >= 2)
	{
		if (eat(organisms,del))
		{
			body = sprites->PredatorEat;
			return;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = sprites->PredatorReprod;
			return;
		}
	}
	body = (sprites)->PredatorMove;
	move(organisms, sizeAqua);
}

bool Predator::eat(std::list<Organism*>& organisms, std::set<Organism*>& del)
{
	Organism*  choice = nullptr;
	int minWay = 10000;
	for (auto u = organisms.begin(); u != organisms.end(); u++)
	{
		if (((*u)->getCoef() == coefOfHerbivore) && (*u != this))
		{
			if (radOfDisp >= way((*u)->getLocation()) && way((*u)->getLocation()) < minWay)
			{
				minWay = way((*u)->getLocation());
				choice = *u;
			}
		}
	}
	if (choice!=nullptr)
	{
		location = (choice)->getLocation();
		starvation = eatTime;
		//(*choice)->died(organisms);
		del.insert(choice);
		return true;
	}
	else
	{
		return false;
	}
}

bool Predator::reproduce(std::list<Organism*>& organisms)
{
	std::list<Organism*>::iterator  choice = organisms.end();
	int minWay = 10000;
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
		location =(* choice)->getLocation();
		reproduction = 0;
		(*choice)->reproductionUp();
		int chance = rand() % 1 + 2;
		while (chance)
		{
			organisms.push_back(new Predator(location, rand() % 1 + 6, rand() % 4 + 6, rand() % 5 + 15, rand() % 3 + 4, sprites));
			chance--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Predator::move(std::list<Organism*>& organisms, coordinates sizeAqua)
{
	float minDist = sizeAqua.first*sizeAqua.second*sizeAqua.third;

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

		coordinates newLoc(location.first, location.second,location.third);
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
									distance += way(coordinates(location.first+i,location.second+j,
										location.third+h),u->getLocation());
								}
								if (distance < minDist)
								{
									minDist = distance;
									newLoc = coordinates(location.first + i, location.second + j,location.third+h);
								}
							}
						}
					}
				}
			}

			location = newLoc;
		}
	}
	if ((organisms.size() == 1) || (minDist == sizeAqua.first*sizeAqua.second*sizeAqua.third))
	{
		int newx = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.first + newx > sizeAqua.first)
		{
			newx = sizeAqua.first - location.first;
		}
		if (location.first + newx <0)
		{
			newx = 0 - location.first;
		}
		int newy = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.second + newy > sizeAqua.second)
		{
			newy = sizeAqua.second - location.second;
		}
		if (location.second + newy <0)
		{
			newy = 0 - location.second;
		}
		int newz = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.third + newz > sizeAqua.third)
		{
			newz = sizeAqua.third - location.third;
		}
		if (location.third + newz <0)
		{
			newz = 0 - location.third;
		}
		location = coordinates(location.first + newx, location.second + newy,location.third+newz);
	}

}