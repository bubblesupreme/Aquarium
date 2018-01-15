#include "Predator.h"



Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int starvation_, int eatTime_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, starvation_, eatTime_)
{}


Predator::~Predator()
{}

void Predator::move(std::map<Organism&, int> neighbors)
{

}