#include "aquarium.h"
#include "Drawer.h"
#include "SFML\Graphics.hpp"
int main()
{
	std::vector<Organism*> listOfOrganisms;

	int chance = rand() % 4 + 3;
	while (chance)
	{
		coordinates posOfHerbivore;
		posOfHerbivore.first = 0;
		posOfHerbivore.second = 0;
		int radOfView = rand() % 3 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 3 + 8;
		int eattime = rand() % 1 + 4;
		int location = rand() % 20 + 1;
		posOfHerbivore.first += location;
		posOfHerbivore.second += location;
		listOfOrganisms.push_back(&Herbivore(posOfHerbivore, radOfDisp, radOfView, lifeTime, eattime));
		chance--;
	}
	chance = rand() % 10 + 5;
	while (chance)
	{
		coordinates posOfPlankton;
		posOfPlankton.first = 0;
		posOfPlankton.second = 0;
		int radOfView = rand() % 3 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 3 + 8;
		int eattime = rand() % 1 + 4;
		int location = rand() % 20 + 1;
		posOfPlankton.first += location;
		posOfPlankton.second += location;
		listOfOrganisms.push_back(&Plankton(posOfPlankton, radOfDisp, radOfView, lifeTime));
		chance--;
	}
	chance = rand() % 3 + 2;
	while (chance)
	{
		coordinates posOfPredators;
		posOfPredators.first = 0;
		posOfPredators.second = 0;
		int radOfView = rand() % 3 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 3 + 8;
		int eattime = rand() % 1 + 4;
		int location = rand() % 20 + 1;
		posOfPredators.first += location;
		posOfPredators.second += location;
		listOfOrganisms.push_back(&Predator(posOfPredators, radOfDisp, radOfView, lifeTime, eattime));
		chance--;
	}
	coordinates size;
	size.first = 100;
	size.second = 100;
	Aquarium aq(size, listOfOrganisms);
	aq.show();
	sf::RenderWindow window(sf::VideoMode(size.first, size.second), "Aquarium");
	std::string mapPath = "map.png";
	Drawer aquaDraw(&window,size,mapPath);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		aquaDraw.drawAquarium();
		aquaDraw.drawOrganisms(aq.getListOfOrganisms());
		window.display();
	}
}
