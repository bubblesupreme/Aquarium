#pragma once
#include "Header.h"
///
class Fish
{
public:
	void update() { std::cout << "it works" << std::endl; }
};
class Predator
{
public:
	void update() { std::cout << "it works" << std::endl; }
};
//class Plankton
//{
//public:
//	void update() { std::cout << "it works" << std::endl; }
//};
///
class Aquarium
{
public:
	Aquarium(std::pair<double, double> size) :size(size){}
	Aquarium(std::pair<double, double> size, std::vector<Fish*> listOfFishs,
		std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators);
	~Aquarium();
	//void show();
	void update();


private:
	std::pair<double, double> size;
	std::vector<Fish*> listOfFishs;
	std::vector<Plankton*> listOfPlanktons;
	std::vector<Predator*> listOfPredators;
};

