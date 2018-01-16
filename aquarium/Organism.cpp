#include "Organism.h"

Organism::Organism(coordinates location_, int radOfDisp_, int radOfView_,
	int lifeTime_, int pauseReprodaction_) : lifeTime(lifeTime_), radOfDisp(radOfDisp_),
	radOfView(radOfView_), pauseReprodaction(pauseReprodaction_), reprodaction(0) {};

void Organism::moveDisl(coordinates dislocation)
{
	location = dislocation;
};

void Organism::life()
{
	lifeTime--;
	reprodaction++;
}

void Organism::reproduce()
{
	reprodaction=0;
}

int Organism::getPauseReprodaction() const
{
	return pauseReprodaction;
}

int Organism::getRadOfView()const
{
	return radOfView;
};

int Organism::getRadOfDisp()const
{
	return radOfDisp;
};

int Organism::getLifeTime()const
{
	return lifeTime;
};

int Organism::getReprodaction() const
{
	return reprodaction;
}

coordinates Organism::getLocation()const
{
	return location;
};