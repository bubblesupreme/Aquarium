#ifndef PLANKTON_H
#define PLANKTON_H

#include "Organism.h"


/*  radOfView: 2-4
    radOfDisp: 1-3
	lifeTime: 10-15 days
	pauseReprodaction: 2
*/

class Plankton :
	public Organism
{
public:
	Plankton(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, Sprites* sprites_);
	virtual ~Plankton();
	//using Organism::update;
	virtual void update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del) override;
private:
	virtual bool reproduce(std::list<Organism*>& organisms) override;
	virtual void move(std::list<Organism*>& organisms, coordinates sizeAqua) override;
};


#endif
