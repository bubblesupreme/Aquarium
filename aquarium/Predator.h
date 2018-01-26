#ifndef PREDATOR_H
#define PREDATOR_H

#include "Fish.h"

/*  radOfView: 6-10
    radOfDisp: 6-7
    lifeTime: 4-5 days
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
	virtual bool update(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
private:
	bool eat(std::vector<Organism*>& organisms) override;
	virtual bool reproduce(std::vector<Organism*>& organisms) override;
	virtual void move(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
};

#endif