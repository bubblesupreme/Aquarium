#ifndef ORGANISM_H
#define ORGANISM_H

#include "Exception.h"
#include <map>
#include <cstdlib>

typedef std::pair<int, int> coordinates;

class Organism
{
public:
	Organism(coordinates location_, int radOfDisp_, int radOfView_,
		int lifeTime_, int starvation_);
	virtual ~Organism() = 0;
	void moveDisl(coordinates dislocation);
	virtual void move(std::map<Organism&, int> neighbors, coordinates sizeAqua) = 0;
	void life();
	int getRadOfView()const;
	int getRadOfDisp()const;
	int getLifeTime() const;
	int getReprodaction() const;
	coordinates getLocation()const;
protected:
	int lifeTime;
	int reprodaction;
	const int radOfView;
	const int radOfDisp;
	coordinates location;
};

#endif