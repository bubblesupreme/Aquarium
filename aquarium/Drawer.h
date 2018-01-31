#ifndef DRAWER_H
#define DRAWER_H
#include "aquarium.h"
#include "Enum.h"

class Drawer
{
public:
	Drawer(sf::RenderWindow& renderWindow, coordinates coord, std::string aquaImagePath);
	void drawOrganisms(std::list<Organism*>& organisms,Plan plan);
	void drawAquarium(Plan plan);
	bool animationUpdate(std::list<Organism*>&listOfOrganisms, Plan plan);
	void diedAnimation();
	~Drawer();
private:
	sf::RenderWindow* renderWindow;
	coordinates size;
	sf::Sprite s_map;
	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_plant;
	sf::Texture plant;
	sf::Sprite s_bubble1;
	sf::Sprite s_bubble2;
	sf::Texture bubble;
	sf::Font fontToPlan;
	sf::Text planText1;
	sf::Text planText2;
	sf::Text planText3;
	float stepPlant = 0.02;
	float stepBubble = -1;
	const int SIZE = 45;
};
#endif DRAWER_H
