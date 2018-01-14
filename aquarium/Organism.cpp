#include "Organism.h"

Organism::Organism(coordinates location_, int radOfDisp_, int radOfView_,
	int lifeTime_, int starvation_) : lifeTime(lifeTime_), radOfDisp(radOfDisp_), radOfView(radOfView_) {};

void Organism::moveDisl(coordinates dislocation)
{
	location = dislocation;
};

void Organism::life()
{
	lifeTime--;
}

int Organism::getRadOfView()
{
	return radOfView;
};

int Organism::getRadOfDisp()
{
	return radOfDisp;
};

int Organism::getLifeTime()
{
	return lifeTime;
};

coordinates Organism::getLocation()
{
	return location;
};