#include "Drawer.h"
int SIZE = 35;
Drawer::~Drawer()
{
}
Drawer::Drawer(sf::RenderWindow& renderWindow, coordinates size, std::string aquaImagePath)
{
	map.loadFromFile(aquaImagePath);
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	this->renderWindow = &renderWindow;
	this->size = size;

}
void Drawer::drawOrganisms(std::vector<Organism*>& listOfOrganisms,int plan)
{
	std::cout << "\n\n"<<listOfOrganisms.size()<<"   ";
	if (plan == 1)
	{
		for (auto i = listOfOrganisms.rbegin(); i != listOfOrganisms.rend(); i++)
		{
			//organismSprite->setPosition(((*i)->getLocation().second*20), ((*i)->getLocation().first*20));
			//(*i)->draw(renderWindow);
			(*i)->getSprite()->setPosition(((*i)->getLocation().first * SIZE), ((*i)->getLocation().second * SIZE));
			renderWindow->draw(*(*i)->getSprite());
			//renderWindow->draw(organismSprite);
			std::cout << (*i)->getLocation().first << "-" << (*i)->getLocation().second << "  ";
		}
	}
	else if (plan == 2) 
	{
		for (auto i = listOfOrganisms.rbegin(); i != listOfOrganisms.rend(); i++)
		{
			//organismSprite->setPosition(((*i)->getLocation().second*20), ((*i)->getLocation().first*20));
			//(*i)->draw(renderWindow);
			(*i)->getSprite()->setPosition(((*i)->getLocation().first * SIZE), ((*i)->getLocation().third * SIZE));
			renderWindow->draw(*(*i)->getSprite());
			//renderWindow->draw(organismSprite);
			std::cout << (*i)->getLocation().first << "-" << (*i)->getLocation().third << "  ";
		}
	}
	else
	{
		for (auto i = listOfOrganisms.rbegin(); i != listOfOrganisms.rend(); i++)
		{
			//organismSprite->setPosition(((*i)->getLocation().second*20), ((*i)->getLocation().first*20));
			//(*i)->draw(renderWindow);
			(*i)->getSprite()->setPosition(((*i)->getLocation().second * SIZE), ((*i)->getLocation().third* SIZE));
			renderWindow->draw(*(*i)->getSprite());
			//renderWindow->draw(organismSprite);
			std::cout << (*i)->getLocation().second << "-" << (*i)->getLocation().third << "  ";
		}
	}
}
void Drawer::drawAquarium(int plan)
{
	sf::Font fontToPlan;
	fontToPlan.loadFromFile("CyrilicOld.ttf");
	sf::Text planText1("Y/X", fontToPlan, 40);
	planText1.setFillColor(sf::Color::Green);
	planText1.setPosition(0,0);
	sf::Text planText2("Z/X", fontToPlan, 40);
	planText2.setFillColor(sf::Color::Green);
	planText2.setPosition(0, 0);
	sf::Text planText3("Z/Y", fontToPlan, 40);
	planText3.setFillColor(sf::Color::Green);
	planText3.setPosition(0, 0);
	
	
	if (plan == 1)
	{
		for (int i = 0; i < size.second; i++)
		{
			for (int j = 0; j < size.first; j++)
			{
				s_map.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
				s_map.setPosition(j * SIZE, i * SIZE);
				renderWindow->draw(s_map);
				renderWindow->draw(planText1);
			}
		}
	}
	else if (plan == 2)
	{
		for (int i = 0; i < size.third; i++)
		{
			for (int j = 0; j < size.first; j++)
			{
				s_map.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
				s_map.setPosition(j * SIZE, i * SIZE);
				renderWindow->draw(s_map);
				renderWindow->draw(planText2);
			}
		}
	}
	else
	{
		for (int i = 0; i < size.second; i++)
		{
			for (int j = 0; j < size.third; j++)
			{
				s_map.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
				s_map.setPosition(j * SIZE, i * SIZE);
				renderWindow->draw(s_map);
				renderWindow->draw(planText3);
			}
		}
	}
	//renderWindow->draw(s_map);
	
}
