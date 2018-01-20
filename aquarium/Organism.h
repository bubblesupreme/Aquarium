#ifndef ORGANISM_H
#define ORGANISM_H

#include "Exception.h"
#include "Constants.h"
#include "Sprites.h"
//#include <SFML\Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

typedef std::pair<int, int> coordinates;

class Organism
{
public:
	Organism(coordinates location_, int radOfDisp_, int radOfView_,
		int lifeTime_, int pauseReprodaction_, int coef_, sf::Sprite body_);
	virtual ~Organism();
	virtual bool update(std::vector<Organism*>& organisms, coordinates sizeAqua) = 0;
	virtual void move(std::vector<Organism*>& organisms, coordinates sizeAqua) = 0;
	void died(std::vector<Organism*>& organisms);
	void reproductionUp();
	int getCoef() const;
	int getReprodaction() const;
	int getPauseReprodaction() const;
	sf::Sprite getSprite() const;
	coordinates getLocation()const;
protected:
	sf::Sprite& body;
	int way(coordinates neighbors);
	virtual bool reproduce(std::vector<Organism*>& organisms) = 0;
	int lifeTime;
	int reproduction;
	const int pauseReprodaction;
	const int radOfView;
	const int radOfDisp;
	const int coef;
	coordinates location;
	Sprites sprites;
};

#endif