#ifndef SPRITES_H
#define SPRITES_H

#include <SFML\Graphics.hpp>

static sf::Sprite creatSprite(const std::string& fileName)
{
	sf::Image image;
	image.loadFromFile(fileName);
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite body;
	body.setTexture(texture);
	return body;
}

static sf::Sprite HerbivoreEat = creatSprite("HrbvEat.png");
static sf::Sprite HerbivoreMove = creatSprite("HrbvMove.png");
static sf::Sprite HerbivoreReprod = creatSprite("HrbvReprod.png");
static sf::Sprite PredatorEat = creatSprite("PrdEat.png");
static sf::Sprite PredatorMove = creatSprite("PrdMove.png");
static sf::Sprite PredatorReprod = creatSprite("PrdReprod.png");
static sf::Sprite PlanktonMove = creatSprite("PlnkMove.png");
static sf::Sprite PlanktonReprod = creatSprite("PlnkReprod.png");

#endif