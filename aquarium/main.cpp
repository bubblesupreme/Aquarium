#include "aquarium.h"
#include "Drawer.h"
#include <iostream>
#include "Plankton.h"
#include "Herbivore.h"
#include "Predator.h"
void main()
{
	std::vector<Organism*> listOfOrganisms;


	int chance = rand() % 10 + 5;
	while (chance)
	{
		coordinates posOfPlankton;
		posOfPlankton.first = 0;
		posOfPlankton.second = 0;
		int radOfView = rand() % 2 + 2;
		int radOfDisp = rand() % 2 + 1;
		int lifeTime = rand() % 2 + 3;
		int location = rand() % 20 + 1;
		posOfPlankton.first += location;
		posOfPlankton.second += location;
		try
		{
			listOfOrganisms.push_back(new Plankton(posOfPlankton, radOfDisp, radOfView, lifeTime));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}

	chance = rand() % 4 + 3;
	while (chance)
	{
		coordinates posOfHerbivore;
		posOfHerbivore.first = 0;
		posOfHerbivore.second = 0;
		int radOfView = rand() % 2 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 3 + 8;
		int eattime = rand() % 1 + 4;
		int location = rand() % 20 + 1;
		posOfHerbivore.first += location;
		posOfHerbivore.second += location;
		try
		{
			listOfOrganisms.push_back(new Herbivore(posOfHerbivore, radOfDisp, radOfView, lifeTime, eattime));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}
	
	chance = rand() % 3 + 2;
	while (chance)
	{
		coordinates posOfPredators;
		posOfPredators.first = 0;
		posOfPredators.second = 0;
		int radOfView = rand() % 4 + 6;
		int radOfDisp = rand() % 1 + 6;
		int lifeTime = rand() % 1 + 4;
		int eattime = rand() % 1 + 2;
		int location = rand() % 20 + 1;
		posOfPredators.first += location;
		posOfPredators.second += location;
		try
		{
			listOfOrganisms.push_back(new Predator(posOfPredators, radOfDisp, radOfView, lifeTime, eattime));
		}
		catch (Exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		chance--;
	}
	coordinates size;
	size.first = 40;
	size.second = 30;
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Event e;
	const int UPDATING = 0, MODIFYING = 1;
	int state = MODIFYING;
	//Aquarium aquarium(coordinates(40, 30));
	try
	{
		Aquarium aq(size, listOfOrganisms);
		std::string mapPath = "pp.png";
		Drawer aquaDraw(window, size, mapPath);
		while (window.isOpen()) {

			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
				}

				if (e.type == sf::Event::KeyPressed) {

					switch (e.key.code) {
					case sf::Keyboard::Escape:
						window.close();
						break;

					case sf::Keyboard::Return:
						switch (state) {

						case UPDATING:
							state = MODIFYING;
							break;

						case MODIFYING:
							state = UPDATING;

						default:
							break;
						}
						break;

					case sf::Keyboard::Right: {
						state = UPDATING;
						break;
					}

					default:
						break;
					}
				}

				if (e.type == sf::Event::KeyReleased) {

					switch (e.key.code) {

					case sf::Keyboard::Right: {
						state = MODIFYING;
						break;
					}
					default:
						break;
					}
				}
			}

			if (state == UPDATING) {
				aq.update();
				
			}
			aq.show();
			window.clear();




			aquaDraw.drawAquarium();
			aquaDraw.drawOrganisms(aq.getListOfOrganisms());
			window.display();
		}
	}
	catch (Exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	std::cin.get();
}
