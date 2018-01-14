#ifndef PREDATOR_H
#define PREDATOR_H

#include "Fish.h"

class Predator :
	public Fish
{
public:
	Predator(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int starvation_, int eatTime_);
	virtual ~Predator();
	virtual void move(std::map<Organism&, int> neighbors) override;
};

#endif