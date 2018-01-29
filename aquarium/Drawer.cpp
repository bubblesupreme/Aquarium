#include "Drawer.h"
const int SIZE = 35;
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
	this->fontToPlan.loadFromFile("CyrilicOld.ttf");
	this->planText1 = sf::Text("Y/X", fontToPlan, 40);
	planText1.setFillColor(sf::Color::Green);
	planText1.setPosition(0, 0);
	this->planText2 = sf::Text("Z/X", fontToPlan, 40);
	planText2.setFillColor(sf::Color::Green);
	planText2.setPosition(0, 0);
	this->planText3 = sf::Text("Z/Y", fontToPlan, 40);
	planText3.setFillColor(sf::Color::Green);
	planText3.setPosition(0, 0);

}
bool Drawer::animationUpdate(std::list<Organism*>&listOfOrganisms, float time)
{
	bool flag = false;///если true то нужно отрисовывать
	for (auto org : listOfOrganisms)
	{
		if ((org->getPrevLocation().first != org->getLocation().first)||
			(org->getPrevLocation().second != org->getLocation().second)||
			(org->getPrevLocation().third != org->getLocation().third))
		{
			float x = org->getPrevLocation().first;
			float y = org->getPrevLocation().second;
			float y2 = org->getLocation().second;
			float x2 = org->getLocation().first;
			float z = org->getPrevLocation().third;
			float z2 = org->getLocation().third;
			float distance = sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y) + (z2 - z)*(z2 - z));
			double speed = 0;
			if (org->getCoef() == coefOfHerbivore)
			{
				speed = speedHerbivore;
			}
			else if (org->getCoef() == coefOfPlancton)
			{
				speed = speedPlancton;
			}
			else
			{
				speed = speedPredator;
			}
			if (distance > 2)
			{
				x += speed*time*(x2 - x) / distance;//идем по иксу с помощью вектора нормали
				y += speed*time*(y2 - y) / distance;//идем по игреку так же
				z += speed*time*(z2 - z) / distance;
				coordinates coor(x, y, z);
				org->setPrevLocation(coor);
				flag = true;
			}
		}
	}
	return flag;
}
void Drawer::diedAnimation()
{
	sf::Font fontToDied;
	fontToDied.loadFromFile("CyrilicOld.ttf");
	sf::Text diedText("Aquarium died", fontToDied, 150);
	diedText.setFillColor(sf::Color::Red);
	diedText.setPosition(size.first / 2, size.second / 2);
	renderWindow->draw(diedText);
}
void Drawer::drawOrganisms(std::list<Organism*>& listOfOrganisms, int plan)
{
	//std::cout << "\n\n"<<listOfOrganisms.size()<<"   ";
	if (plan == 1)
	{
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().first*SIZE + 40, i->getPrevLocation().second*SIZE + 40);
			renderWindow->draw(sp);
		}
	}
	else if (plan == 2)
	{
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().first*SIZE + 40, i->getPrevLocation().third*SIZE + 40);
			renderWindow->draw(sp);
			//std::cout << i->getLocation().first << "-" << i->getLocation().third << "  ";
		}
	}
	else
	{
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().second*SIZE + 40, i->getPrevLocation().third*SIZE + 40);
			renderWindow->draw(sp);
			//std::cout << i->getLocation().second << "-" << i->getLocation().third << "  ";
		}
	}
}
void Drawer::drawAquarium(int plan)
{
	if (plan == 1)
	{
		for (int i = 0; i < size.second; i++)
		{
			for (int j = 0; j < size.first; j++)
			{
				s_map.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
				s_map.setPosition(j * SIZE+40, i * SIZE+40);
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
				s_map.setPosition(j * SIZE + 40, i * SIZE + 40);
				renderWindow->draw(s_map);
				renderWindow->draw(planText2);
			}
		}
	}
	else
	{
		for (int i = 0; i < size.third; i++)
		{
			for (int j = 0; j < size.second; j++)
			{
				s_map.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
				s_map.setPosition(j * SIZE + 40, i * SIZE + 40);
				renderWindow->draw(s_map);
				renderWindow->draw(planText3);
			}
		}
	}

}