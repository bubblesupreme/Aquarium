#include "Fish.h"



Fish::Fish(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_, int pauseReprodaction_) : Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, pauseReprodaction_), eatTime(eatTime_)
{}

int Fish::getStarvation()const
{
	return starvation;
}

void Fish::hunger()
{
	starvation--;
}

void Fish::eat()
{
	starvation = eatTime;
}

int Fish::getEatTime() const
{
	return eatTime;
}