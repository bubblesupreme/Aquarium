#include "Fish.h"



Fish::Fish(coordinates location_, int radOfDisp_, int radOfview_, int lifeTime_, 
	int eatTime_, int pauseReprodaction_, int coef_, bool sex_,Sprites* sprites_)
	: Organism(location_, radOfDisp_, radOfview_,lifeTime_, pauseReprodaction_, 
		coef_, sex_, sprites_), eatTime(eatTime_), starvation(eatTime_)
{}

Fish::~Fish()
{}