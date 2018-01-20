#include "Drawer.h"

Drawer::~Drawer()
{
}
Drawer::Drawer(sf::RenderWindow& renderWindow, coordinates size, std::string aquaImagePath)
{
	sf::Image map_image;
	map_image.loadFromFile(aquaImagePath);
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);
	this->renderWindow = &renderWindow;
	this->size = size;
}
void Drawer::drawOrganisms(std::vector<Organism*> listOfOrganisms)
{
	for (auto i : listOfOrganisms)
	{
		sf::Sprite organismSprite = i->getSprite();
		organismSprite.setPosition((i->getLocation().second), (i->getLocation().first));
		renderWindow->draw(organismSprite);
	}
}
void Drawer::drawAquarium()
{
	
	for (int i = 0; i < size.second; i++)
	{
		for (int j = 0; j < size.first; j++)
		{
			s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
			s_map.setPosition(j, i);
			renderWindow->draw(s_map);
		}
	}
}
