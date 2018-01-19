#include "aquarium.h"
#include "Drawer.h"
#include "SFML\Graphics.hpp"

void main()
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
	sf::RenderWindow window(sf::VideoMode(858, 600, 32), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(10);
	sf::Event e;
	const int UPDATING = 0, MODIFYING = 1;
	int state = MODIFYING;
	Aquarium aquarium(coordinates(40, 30));
	std::string mapPath = "map.png";
	Drawer aquaDraw(&window, size, mapPath);
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
			aquarium.update();
		}

		window.clear();
		aquaDraw.drawAquarium();
		aquaDraw.drawOrganisms(aq.getListOfOrganisms());
		window.display();
	}
}
