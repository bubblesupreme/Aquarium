#pragma once

#include "Organism.h"

class Plankton :
	public Organism
{
public:
	Plankton(coordinates location_, int radOfDisp_, int radOfview_,
		int lifeTime_, int starvation_);
	virtual ~Plankton();
	virtual void move(std::map<Organism&, int> neighbors) override;
};

