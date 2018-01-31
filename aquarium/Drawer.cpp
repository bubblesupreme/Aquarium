#include "Drawer.h"

Drawer::~Drawer()
{
}
Drawer::Drawer(sf::RenderWindow& renderWindow, coordinates size, std::string aquaImagePath)
{
	map.loadFromFile(aquaImagePath);

	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	s_map.scale(1.7, 1.7);
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
	plant.loadFromFile("plant.png");
	s_plant.setTexture(plant);
	s_plant.setPosition(-20,600);
	s_plant.setScale(0.5, 0.5);
	s_plant.setRotation(2);
	bubble.loadFromFile("bubble.png");
	s_bubble1.setTexture(bubble);
	s_bubble1.setScale(0.3, 0.3);
	s_bubble1.setPosition(20, 500);
	s_bubble2.setTexture(bubble);
	s_bubble2.setScale(0.5, 0.5);
	s_bubble2.setPosition(850, 450);
}
bool Drawer::animationUpdate(std::list<Organism*>&listOfOrganisms, Plan plan)
{
	bool flag = false;///если true то нужно отрисовывать
	switch (plan)
	{
	case XY:
		for (auto org : listOfOrganisms)
		{
			if ((org->getPrevLocation().first != org->getLocation().first) ||
				(org->getPrevLocation().second != org->getLocation().second) ||
				(org->getPrevLocation().third != org->getLocation().third))
			{
				float x = org->getPrevLocation().first;
				float y = org->getPrevLocation().second;
				float y2 = org->getLocation().second;
				float x2 = org->getLocation().first;
				float z = org->getPrevLocation().third;
				float z2 = org->getLocation().third;
				float distance = sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y));// +(z2 - z)*(z2 - z));
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
				if (distance > 1)
				{
					x += speed*(x2 - x) / distance;
					y += speed*(y2 - y) / distance; \
						z += speed*(z2 - z) / distance;
					coordinates coor(x, y, z);
					org->setPrevLocation(coor);
					flag = true;
				}
			}
		}
		break;
	case XZ:
		for (auto org : listOfOrganisms)
		{
			if ((org->getPrevLocation().first != org->getLocation().first) ||
				(org->getPrevLocation().second != org->getLocation().second) ||
				(org->getPrevLocation().third != org->getLocation().third))
			{
				float x = org->getPrevLocation().first;
				float y = org->getPrevLocation().second;
				float y2 = org->getLocation().second;
				float x2 = org->getLocation().first;
				float z = org->getPrevLocation().third;
				float z2 = org->getLocation().third;
				float distance = sqrt((x2 - x)*(x2 - x) + (z2 - z)*(z2 - z));// +(z2 - z)*(z2 - z));
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
				if (distance > 1)
				{
					x += speed*(x2 - x) / distance;
					y += speed*(y2 - y) / distance; \
						z += speed*(z2 - z) / distance;
					coordinates coor(x, y, z);
					org->setPrevLocation(coor);
					flag = true;
				}
			}
		}
		break;
	case ZY:
		for (auto org : listOfOrganisms)
		{
			if ((org->getPrevLocation().first != org->getLocation().first) ||
				(org->getPrevLocation().second != org->getLocation().second) ||
				(org->getPrevLocation().third != org->getLocation().third))
			{
				float x = org->getPrevLocation().first;
				float y = org->getPrevLocation().second;
				float y2 = org->getLocation().second;
				float x2 = org->getLocation().first;
				float z = org->getPrevLocation().third;
				float z2 = org->getLocation().third;
				float distance = sqrt((y2 - y)*(y2 - y) + (z2 - z)*(z2 - z));// +(z2 - z)*(z2 - z));
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
				if (distance > 1)
				{
					x += speed*(x2 - x) / distance;
					y += speed*(y2 - y) / distance; \
						z += speed*(z2 - z) / distance;
					coordinates coor(x, y, z);
					org->setPrevLocation(coor);
					flag = true;
				}
			}
		}
		break;
	}
	float rotation = s_plant.getRotation();
	if (rotation> 2.0f|| rotation < 0.1f)
	{
		stepPlant = stepPlant*(-1);

	}
	s_plant.setRotation(rotation + stepPlant);
	float posBubble = s_bubble1.getPosition().y;
	if (posBubble > 501.0f || posBubble <300.0f)
	{
		stepBubble = stepBubble*(-1);
	}
	s_bubble1.setPosition(20, s_bubble1.getPosition().y + stepBubble);
	s_bubble2.setPosition(850, s_bubble2.getPosition().y + (-1)*stepBubble);

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
void Drawer::drawOrganisms(std::list<Organism*>& listOfOrganisms, Plan plan)
{
	switch (plan)
	{
	case XY:
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().first*SIZE, i->getPrevLocation().second*SIZE);
			renderWindow->draw(sp);
		}
		break;
	case XZ:
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().first*SIZE, i->getPrevLocation().third*SIZE);
			renderWindow->draw(sp);
		}
		break;
	case ZY:
		for (auto i : listOfOrganisms)
		{
			sf::Sprite sp = i->getSprite();
			sp.setPosition(i->getPrevLocation().second*SIZE, i->getPrevLocation().third*SIZE);
			renderWindow->draw(sp);
		}
		break;
	default:
		break;
	}
	renderWindow->draw(s_plant);
	renderWindow->draw(s_bubble1);
	renderWindow->draw(s_bubble2);
}
void Drawer::drawAquarium(Plan plan)
{
	switch (plan)
	{
	case XY:
		renderWindow->draw(planText1);
		break;
	case XZ:
		renderWindow->draw(planText2);
		break;
	case ZY:
		renderWindow->draw(planText3);
		break;
	default:
		break;
	}
	renderWindow->draw(s_map);

}