#ifndef ORGANISM_H
#define ORGANISM_H

#include "Exception.h"
#include "Constants.h"
#include "Sprites.h"
#include "coordinates.h"
//#include <SFML\Graphics.hpp>
#include <list>
#include <cstdlib>
#include <iostream>
#include <set>


class Organism
{
public:
	Organism(coordinates location_, int radOfDisp_, int radOfView_,
		int lifeTime_, int pauseReprodaction_, int coef_, Sprites* sprites_);
	virtual ~Organism();
	virtual void update(std::list<Organism*>& organisms, coordinates sizeAqua, std::set<Organism*>& del) = 0;
	virtual void move(std::list<Organism*>& organisms, coordinates sizeAqua) = 0;
	//void died(std::list<Organism*>& organisms);
	void reproductionUp();
	int getCoef() const;
	int getReprodaction() const;
	int getPauseReprodaction() const;
	sf::Sprite getSprite() const;
	coordinates getLocation()const;
	
protected:
	sf::Sprite body;
	int way(coordinates neighbors);
	int way(coordinates this_,coordinates neighbors);
	virtual bool reproduce(std::list<Organism*>& organisms) = 0;
	int lifeTime;
	int reproduction;
	const int pauseReprodaction;
	const int radOfView;
	const int radOfDisp;
	const int coef;
	coordinates location;
	Sprites* sprites;
};

#endif