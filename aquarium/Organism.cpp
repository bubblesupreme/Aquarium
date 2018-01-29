#include "Organism.h"

Organism::Organism(coordinates location_, int radOfDisp_, int radOfView_,
	int lifeTime_, int pauseReprodaction_, int coef_,bool sex_, Sprites* sprites_)
	: lifeTime(lifeTime_), radOfDisp(radOfDisp_), radOfView(radOfView_), sprites(sprites_),
	pauseReprodaction(pauseReprodaction_), reproduction(0), coef(coef_),sex(sex_),location(location_),
	prevLocation(location_)
{};



Organism::~Organism()
{}

bool Organism::getSex()const
{
	return sex;
}

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

sf::Sprite Organism::getSprite() const
{
	return body;
}

coordinates Organism::getPrevLocation()const
{
	return prevLocation;
}

void Organism::setLocation(coordinates loc)
{
	location = loc;
}

void Organism::setPrevLocation(coordinates loc)
{
	prevLocation = loc;
}
//void Organism::died(std::list<Organism*>& organisms)
//{
//	for (auto i=organisms.begin();i!=organisms.end();i++)
//	{
//		if (*i == this)
//		{
//			this->~Organism();
//			return;
//		}
//	}
//}

int Organism::way(coordinates neighbors) const
{
	return sqrt((neighbors.first - location.first)*(neighbors.first - location.first)
		+ (neighbors.second - location.second)*(neighbors.second - location.second)
		+ (neighbors.third - location.third)*(neighbors.third - location.third));
}

int Organism::way(coordinates this_, coordinates neighbors) const
{
	return sqrt((neighbors.first - this_.first)*(neighbors.first - this_.first)
		+ (neighbors.second - this_.second)*(neighbors.second - this_.second)
		+ (neighbors.third - this_.third)*(neighbors.third - this_.third));
}
