#include "Fish.h"



Fish::Fish(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int starvation_, int eatTime_) : Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, starvation_), eatTime(eatTime_)
{}

int Fish::getStarvation()
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