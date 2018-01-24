#include "Organism.h"

Organism::Organism(coordinates location_, int radOfDisp_, int radOfView_,
	int lifeTime_, int pauseReprodaction_, int coef_, sf::Sprite* body_) 
	: lifeTime(lifeTime_), radOfDisp(radOfDisp_), radOfView(radOfView_),
	pauseReprodaction(pauseReprodaction_), reproduction(0), coef(coef_),location(location_)
{
	body = new sf::Sprite;
	body = body_;
	sprites=*(new Sprites);
};



Organism::~Organism()
{}

void Organism::reproductionUp()
{
	reproduction = 0;
}

int Organism::getPauseReprodaction() const
{
	return pauseReprodaction;
}

int Organism::getReprodaction() const
{
	return reproduction;
}

coordinates Organism::getLocation()const
{
	return location;
}

int Organism::getCoef() const
{
	return coef;
}

sf::Sprite* Organism::getSprite() const
{
	return body;
}

void Organism::died(std::vector<Organism*>& organisms)
{
	for (auto i=organisms.begin();i!=organisms.end();i++)
	{
		if (*i == this)
		{
			organisms.erase(i);
			this->~Organism();
			return;
		}
	}
}

int Organism::way(coordinates neighbors)
{
	return sqrt((neighbors.first - location.first)*(neighbors.first - location.first)
		+ (neighbors.second - location.second)*(neighbors.second - location.second)
		+ (neighbors.third - location.third)*(neighbors.third - location.third));
}


