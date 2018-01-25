#ifndef DRAWER_H
#define DRAWER_H
#include "aquarium.h"

class Drawer
{
public:
	Drawer(sf::RenderWindow& renderWindow, coordinates coord, std::string aquaImagePath);
	void drawOrganisms(std::list<Organism*>& organisms,int plan);
	void drawAquarium(int plan);
	~Drawer();
private:
	sf::RenderWindow* renderWindow;
	coordinates size;
	sf::Sprite s_map;
	sf::Image map_image;
	sf::Texture map;

};
#endif DRAWER_H
