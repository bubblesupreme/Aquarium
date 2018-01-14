#pragma once
#include <map>

typedef std::pair<int, int> coordinates;

class Organism
{
public:
	Organism(coordinates location_, int radOfDisp_, int radOfView_,
		int lifeTime_, int starvation_);
	virtual ~Organism()=0;
	void move(coordinates dislocation);
	virtual void move(std::map<Organism&, int> neighbors) = 0;
	void reproduce();
	int getRadOfView();
	int getRadOfDisp();
	int getLifeTime();
protected:
	int lifeTime;
	const int radOfView;
	const int radOfDisp;
	coordinates location;
};

