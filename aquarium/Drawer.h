#ifndef DRAWER_H
#define DRAWER_H
#include "aquarium.h"

class Drawer
{
public:
	Drawer(sf::RenderWindow& renderWindow, coordinates coord, std::string aquaImagePath);
	void drawOrganisms(std::list<Organism*>& organisms,int plan);
	void drawAquarium(int plan);
	bool animationUpdate(std::list<Organism*>&listOfOrganisms, float time);
	void diedAnimation();
	~Drawer();
private:
	sf::RenderWindow* renderWindow;
	coordinates size;
	sf::Sprite s_map;
	sf::Image map_image;
	sf::Texture map;
	sf::Font fontToPlan;
	sf::Text planText1;
	sf::Text planText2;
	sf::Text planText3;
	const int SIZE = 35;
};
#endif DRAWER_H
