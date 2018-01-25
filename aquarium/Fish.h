#ifndef FISH_H
#define FISH_H

#include "Organism.h"

class Fish :
	public Organism
{
public:
	Fish(coordinates location_, int radOfDisp_, int radOfview_,	int lifeTime_,
		int eatTime_, int pauseReprodaction_, int coef_, Sprites* sprites_);
	virtual ~Fish();
	//virtual void update(std::vector<Organism*>& organisms, coordinates sizeAqua) = 0;
	virtual bool eat(std::list<Organism*>& organisms, std::set<Organism*>& del) = 0;
protected:
	const int eatTime;
	int starvation;
};

#endif