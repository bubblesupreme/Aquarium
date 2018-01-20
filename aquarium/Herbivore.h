#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "Fish.h"

/*  radOfView: 6-8
    radOfDisp: 4-6
    lifeTime: 8-11 days
	eatTime: 4-5 days
	pauseReprodaction: 3
*/

class Herbivore :
	public Fish
{
public:
	Herbivore(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int eatTime_);
	virtual ~Herbivore();
	virtual bool update(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
private:
	bool eat(std::vector<Organism*>& organisms) override;
	virtual bool reproduce(std::vector<Organism*>& organisms) override;
	virtual void move(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
};

#endif