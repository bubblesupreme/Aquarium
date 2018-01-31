#include "aquarium.h"
#include "Drawer.h"
#include <iostream>
#include <SFML/Audio.hpp>

void main()
{
	sf::Music music;
	music.openFromFile("music water.wav");
	music.setLoop(true);
	music.play();
	coordinates size(28, 28, 28);
	sf::RenderWindow window(sf::VideoMode(980, 980), "Aquarium", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Event e;
	State state = UPDATING;
	Plan plan=XY;
	int count = 0;
	music.play();
	try
	{
		Aquarium aq(size);
		aq.randFill(200, 255, 30);
		std::string mapPath = "water.png";
		Drawer aquaDraw(window, size, mapPath);
		bool Animation = false;
		while (window.isOpen()) {

			/*float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
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
						plan = XY;
						break;
					case sf::Keyboard::Num2:
						plan = XZ;
						break;
					case sf::Keyboard::Num3:
						plan = ZY;
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
				Animation = aquaDraw.animationUpdate(aq.getListOfOrganisms(),plan);
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
		music.stop();
		std::cout << ex.what() << std::endl;
		music.openFromFile("vertu.wav");
		music.play();
	}
	std::cout << count << std::endl;

	std::cin.get();
}
