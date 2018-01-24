#include "aquarium.h"
#include "Drawer.h"
#include <iostream>
#include "Plankton.h"
#include "Herbivore.h"
#include "Predator.h"
void main()
{
	std::vector<Organism*> listOfOrganisms;


	int chance = rand() % 10 + 120;
	while (chance)
	{
		coordinates posOfPlankton;
		int radOfView = rand() % 2 + 2;
		int radOfDisp = rand() % 2 + 1;
		int lifeTime = rand() % 2 + 3;
		posOfPlankton.first = rand() % 45 + 0;
		posOfPlankton.second = rand() % 24 + 0;
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

	chance = rand() % 4 + 140;
	while (chance)
	{
		coordinates posOfHerbivore;
		int radOfView = rand() % 2 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 3 + 8;
		int eattime = rand() % 1 + 4;
		posOfHerbivore.first = rand() % 45 + 0;
		posOfHerbivore.second = rand() % 24 + 0;
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
	
	chance = rand() % 3 + 60;
	while (chance)
	{
		coordinates posOfPredators;
		int radOfView = rand() % 4 + 6;
		int radOfDisp = rand() % 1 + 6;
		int lifeTime = rand() % 1 + 4;
		int eattime = rand() % 1 + 2;
		posOfPredators.first = rand() % 45 + 0;
		posOfPredators.second = rand() % 24 + 0;
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
	size.first = 45;
	size.second = 24;
	
	sf::RenderWindow window(sf::VideoMode(1800, 960), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Event e;
	const int UPDATING = 0, MODIFYING = 1;
	int state = MODIFYING;
	//Aquarium aquarium(coordinates(40, 30));
	///died
	sf::Font fontToDied;
	fontToDied.loadFromFile("CyrilicOld.ttf");
	sf::Text diedText("Aquarium died",fontToDied,150);
	diedText.setFillColor(sf::Color::Red);
	diedText.setPosition(size.first / 2,size.second/2);
	///
	/*///crowd
	sf::Font fontToCrow;
	fontToCrow.loadFromFile("CyrilicOld.ttf");
	sf::Text diedText("Aquarium died", fontToCrow, 90);
	diedText.setFillColor(sf::Color::Red);
	diedText.setPosition(size.first / 2, size.second / 2);
	///*/

	try
	{
		Aquarium aq(size, listOfOrganisms);
		std::string mapPath = "water.png";
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
			window.clear();
			if (state == UPDATING) 
			{
				aq.update();				
			}

			if (aq.isAlive())
			{
				aquaDraw.drawAquarium();
				aquaDraw.drawOrganisms(aq.getListOfOrganisms());
			}
			else
			{
				window.draw(diedText);
				window.display();
				throw Exception(3);
			}

			aq.show();
			window.display();
			
			
			
		}
	}
	catch (Exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	std::cin.get();
}
