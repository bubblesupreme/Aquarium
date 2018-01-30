#include "aquarium.h"
#include "Drawer.h"
#include <iostream>

void main()
{
	coordinates size(28, 28, 28);
	sf::RenderWindow window(sf::VideoMode(980, 980), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Event e;
	const int UPDATING = 0, MODIFYING = 1;
	int state = UPDATING;
	int plan = 1;
	int count = 0;
	sf::Clock clock;
	try
	{
		Aquarium aq(size);
		aq.randFill(210, 280, 65);
		std::string mapPath = "water.png";
		Drawer aquaDraw(window, size, mapPath);
		bool Animation = false;
		while (window.isOpen()) {

			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();/*
			std::cout <<"  ("<< time << ")";
			time = time / 1000;
			std::cout << "-" << time << "-  ";*/
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
			if (Animation == false)
			{
				if (state == UPDATING)
				{
					aq.update();
					count++;
					std::cout << count << std::endl;
				}
			}
			if (aq.isAlive())
			{
				Animation = aquaDraw.animationUpdate(aq.getListOfOrganisms(), time);
				aquaDraw.drawAquarium(plan);
				aquaDraw.drawOrganisms(aq.getListOfOrganisms(), plan);
			}
			else
			{
				aquaDraw.diedAnimation();
				window.display();
				throw Exception(3);
			}
			window.display();
		}
	}
	catch (Exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	std::cout << count << std::endl;

	std::cin.get();
}
