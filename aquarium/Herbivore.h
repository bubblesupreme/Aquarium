#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "Fish.h"

/*  radOfView: 6-8
    radOfDisp: 4-6
    lifeTime: 8-11 days
	eatTime: 7-9 days
	pauseReprodaction: 4
*/

class Herbivore :
	public Fish
{
public:
	Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int eatTime_, bool sex_,Sprites* sprites_);
	virtual ~Herbivore();
	virtual void update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del) override;
private:
	virtual bool eat(std::list<Organism*>& organisms, std::set<Organism*>& del) override;
	virtual bool reproduce(std::list<Organism*>& organisms) override;
	virtual void move(std::list<Organism*>& organisms, coordinates sizeAqua) override;
};

#endif