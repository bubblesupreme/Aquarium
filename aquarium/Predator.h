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
		int lifeTime_, int eatTime_, Sprites* sprites_);
	virtual ~Predator();
	virtual void update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del) override;
private:
	bool eat(std::list<Organism*>& organisms, std::set<Organism*>& del) override;
	virtual bool reproduce(std::list<Organism*>& organisms) override;
	virtual void move(std::list<Organism*>& organisms, coordinates sizeAqua) override;
};

#endif