#include "Predator.h"
#include <iostream>


Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_, bool sex_,Sprites* sprites_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, pauseReprOfPredator, coefOfPredator,sex_, sprites_)
{
	if ((radOfView > radOfViewPredator + radOfViewPredatorDelta) || (radOfView < radOfViewPredator) ||
		(radOfDisp> radOfDispPredator + radOfDispPredatorDelta) || (radOfDisp < radOfDispPredator) ||
		(lifeTime>lifeTimePredator + lifeTimePredatorDelta) || (lifeTime < lifeTimePredator) ||
		(eatTime>eatTimePredator + eatTimePredatorDelta) || (eatTime < eatTimePredator) ||
		(radOfDisp > radOfView))
	{
		std::cout << radOfDisp << radOfView << lifeTime << coef << std::endl;
		throw Exception(1);
	}
	body = sprites->PredatorMove;
}


Predator::~Predator()
{}

void Predator::update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del)
{
	prevLocation = location;
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation == 0 || lifeTime <= 0)
	{
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
	for (auto org = organisms.begin(); org != organisms.end(); org++)
	{
		if (((*org)->getCoef() == coefOfHerbivore) && (*org != this))
		{
			int curWay=way((*org)->getLocation());
			if (radOfDisp >= curWay && curWay < minWay)
			{
				minWay = curWay;
				choice = *org;
			}
		}
	}
	if (choice!=nullptr)
	{
		location = (choice)->getLocation();
		starvation = eatTime;
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
	for (auto org = organisms.begin(); org != organisms.end(); org++)
	{
		int curWay = way((*org)->getLocation());
		if ((*org != this) & (coef == (*org)->getCoef()) & (*org)->getSex() != this->getSex()
			&((*org)->getReprodaction() >(*org)->getPauseReprodaction()) &(radOfDisp >= curWay))
		{
			if (curWay < minWay)
			{
				minWay = curWay;
				choice = org;
			}
		}
	}
	if (choice!= organisms.end())
	{
		location =(* choice)->getLocation();
		reproduction = 0;
		(*choice)->reproductionUp();
		int chance = childrenOfPredator;
		while (chance)
		{
			int radOfView = rand() % radOfViewPredatorDelta + radOfViewPredator;
			int radOfDisp = rand() % radOfDispPredatorDelta + radOfDispPredator;
			int lifeTime = rand() % lifeTimePredatorDelta + lifeTimePredator;
			int eattime = rand() % eatTimePredatorDelta + eatTimePredator;
			bool sex = rand() % 2;
			organisms.push_back(new Predator(location, radOfDisp, radOfView, lifeTime, eattime,sex, sprites));
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
		for (auto org : organisms)
		{
			if ((org != this) && (radOfView >= way(org->getLocation())) && (org->getCoef() == coefOfHerbivore))
			{
				neighbors.push_back(org);
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
								for (auto neig : neighbors)
								{
									distance += way(coordinates(location.first+i,location.second+j,
										location.third+h), neig->getLocation());
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
		}
		location = newLoc;
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