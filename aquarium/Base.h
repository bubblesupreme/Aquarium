#pragma once
#include "Header.h"
class Base
{
	virtual void move() {}
	virtual void reproduce() {}
	virtual void eat() {}
	int lifeTime;
	int starvation;
	int radOfview;
	int radOfDisp;
	std::pair<double, double> location;
};