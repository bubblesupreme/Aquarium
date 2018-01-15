#ifndef FISH_H
#define FISH_H

#include "Organism.h"

class Fish :
	public Organism
{
public:
	Fish(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int starvation_, int eatTime_, int pauseReprodaction_);
	virtual ~Fish() = 0;
	void hunger();
	int getStarvation() const;
	int getEatTime() const;
	void eat();

protected:
	const int eatTime;
	int starvation;
};

#endif