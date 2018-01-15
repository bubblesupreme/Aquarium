#pragma once
#include "Fish.h"
class Herbivore :
	public Fish
{
public:
	Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int starvation_, int eatTime_);
	virtual ~Herbivore();
	virtual void move(std::map<Organism&, int> neighbors) override;
};

