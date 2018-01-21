#include "Fish.h"



Fish::Fish(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_, int pauseReprodaction_, int coef_, sf::Sprite* body_) 
	: Organism(location_, radOfDisp_, radOfview_,
		lifeTime_, pauseReprodaction_, coef_, body_), eatTime(eatTime_)
{}

Fish::~Fish()
{}