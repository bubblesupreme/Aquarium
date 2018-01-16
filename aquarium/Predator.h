#ifndef PREDATOR_H
#define PREDATOR_H

#include "Fish.h"

/*  radOfView: 6-8
    radOfDisp: 6-7
    lifeTime: 3-5 days
	eatTime: 2-3 days
	pauseReprodaction: 3
*/

class Predator :
	public Fish
{
public:
	Predator(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int eatTime_);
	virtual ~Predator();
	virtual void move(std::map<Organism&, int> neighbors, coordinates sizeAqua) override;
};

#endif