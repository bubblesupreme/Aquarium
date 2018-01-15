#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "Fish.h"

/*  radOfView: 6-9
    radOfDisp: 4-6
    lifeTime: 8-11 days
	eatTime: 4-5 days
*/

class Herbivore :
	public Fish
{
public:
	Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int starvation_, int eatTime_);
	virtual ~Herbivore();
	virtual void move(std::map<Organism&, int> neighbors, coordinates sizeAqua) override;
};

#endif