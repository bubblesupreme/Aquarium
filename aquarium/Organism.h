#ifndef ORGANISM_H
#define ORGANISM_H

#include <map>
#include <cstdlib>

typedef std::pair<int, int> coordinates;

class Organism
{
public:
	Organism(coordinates location_, int radOfDisp_, int radOfView_,
		int lifeTime_, int starvation_);
	virtual ~Organism()=0;
	void moveDisl(coordinates dislocation);
	virtual void move(std::map<Organism&, int> neighbors) = 0;
	void life();
	int getRadOfView();
	int getRadOfDisp();
	int getLifeTime();
	coordinates getLocation();
protected:
	int lifeTime;
	const int radOfView;
	const int radOfDisp;
	coordinates location;
};

#endif