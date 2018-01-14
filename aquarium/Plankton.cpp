#include "Plankton.h"



Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int starvation_):Organism(location_,radOfDisp_,radOfview_,
		lifeTime_, starvation_)
{}


Plankton::~Plankton()
{}

void Plankton::move(std::map<Organism&, int> neighbors)
{
	lifeTime--;
}

