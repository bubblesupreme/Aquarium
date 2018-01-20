#ifndef PLANKTON_H
#define PLANKTON_H

#include "Organism.h"


/*  radOfView: 2-4
    radOfDisp: 1-3
	lifeTime: 3-5 days
	pauseReprodaction: 2
*/

class Plankton :
	public Organism
{
public:
	Plankton(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_);
	virtual ~Plankton();
	//using Organism::update;
	virtual bool update(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
private:
	virtual bool reproduce(std::vector<Organism*>& organisms) override;
	virtual void move(std::vector<Organism*>& organisms, coordinates sizeAqua) override;
};


#endif
