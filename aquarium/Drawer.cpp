#include "Drawer.h"

Drawer::~Drawer()
{
}
Drawer::Drawer(sf::RenderWindow& renderWindow, coordinates size, std::string aquaImagePath)
{
	map.loadFromFile(aquaImagePath, sf::IntRect(0, 0, size.first * 20, size.second * 20));
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	this->renderWindow = &renderWindow;
	this->size = size;

}
void Drawer::drawOrganisms(std::vector<Organism*>& listOfOrganisms)
{
	std::cout << "\n\n"<<listOfOrganisms.size()<<"   ";
	for(auto i=listOfOrganisms.begin();i!=listOfOrganisms.end();i++)
	{
		//organismSprite->setPosition(((*i)->getLocation().second*20), ((*i)->getLocation().first*20));
		//(*i)->draw(renderWindow);
		(*i)->getSprite()->setPosition(((*i)->getLocation().first * 20), ((*i)->getLocation().second * 20));
		renderWindow->draw(*(*i)->getSprite());
		//renderWindow->draw(organismSprite);
		std::cout << (*i)->getLocation().first << "-"<< (*i)->getLocation().second<<"  ";
	}
}
void Drawer::drawAquarium()
{
	
	for (int i = 0; i < size.second; i++)
	{
		for (int j = 0; j < size.first; j++)
		{
			s_map.setTextureRect(sf::IntRect(0, 0, 40, 40));
			s_map.setPosition(j*20, i*20);
			renderWindow->draw(s_map);
		}
	}
	
	//renderWindow->draw(s_map);
	
}
