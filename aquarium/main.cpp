#include "aquarium.h"
#include "Drawer.h"
#include <iostream>
#include "Plankton.h"
#include "Herbivore.h"
#include "Predator.h"
void main()
{
	std::vector<Organism*> listOfOrganisms;
	coordinates size(28,28,28);

	int chance = rand() % 10 + 25;
	while (chance)
	{
		coordinates posOfPlankton;
		int radOfView = rand() % 2 + 2;
		int radOfDisp = rand() % 2 + 1;
		int lifeTime = rand() % 5 + 5;
		posOfPlankton.first = rand() % size.first + 0;
		posOfPlankton.second = rand() % size.second + 0;
		posOfPlankton.third = rand() % size.third + 0;
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

	chance = rand() % 4 + 20;
	while (chance)
	{
		coordinates posOfHerbivore;
		int radOfView = rand() % 2 + 6;
		int radOfDisp = rand() % 2 + 4;
		int lifeTime = rand() % 10 + 20;
		int eattime = rand() % 2 + 7;
		posOfHerbivore.first = rand() % size.first + 0;
		posOfHerbivore.second = rand() % size.second + 0;
		posOfHerbivore.third = rand() % size.third + 0;
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
	
	chance = rand() % 3 + 10;
	while (chance)
	{
		coordinates posOfPredators;
		int radOfView = rand() % 4 + 6;
		int radOfDisp = rand() % 1 + 6;
		int lifeTime = rand() % 5 + 15;
		int eattime = rand() % 3 + 4;
		posOfPredators.first = rand() % size.first + 0;
		posOfPredators.second = rand() % size.second + 0;
		posOfPredators.third = rand() % size.third + 0;
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
	
	sf::RenderWindow window(sf::VideoMode(980, 980), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(30);
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
	int plan = 1;
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
					case sf::Keyboard::Num1:
						plan = 1;
						break;
					case sf::Keyboard::Num2:
						plan = 2;
						break;
					case sf::Keyboard::Num3:
						plan = 3;
						break;
					case sf::Keyboard::Return:
						switch (state) {

						case UPDATING:
							state = MODIFYING;
							break;

						case MODIFYING:
							state = UPDATING;
							break;

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
				aquaDraw.drawAquarium(plan);
				aquaDraw.drawOrganisms(aq.getListOfOrganisms(),plan);
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
