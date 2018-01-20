#ifndef SPRITES_H
#define SPRITES_H

#include <SFML\Graphics.hpp>

 class Sprites
{
public:
	Sprites() 
	{
		
		HerbivoreEatT.loadFromFile("HrbvEat.png", sf::IntRect(0, 0, 20, 20));
		HerbivoreMoveT.loadFromFile("HrbvMove.png", sf::IntRect(0, 0, 20, 20));
		HerbivoreReprodT.loadFromFile("HrbvReprod.png", sf::IntRect(0, 0, 20, 20));
		PredatorEatT.loadFromFile("PrdEat.png", sf::IntRect(0, 0, 20, 20));
		PredatorMoveT.loadFromFile("PrdMove.png", sf::IntRect(0, 0, 20, 20));
		PredatorReprodT.loadFromFile("PrdReprod.png", sf::IntRect(0, 0, 20, 20));
		PlanktonMoveT.loadFromFile("PlnkMove.png", sf::IntRect(0, 0, 20, 20));
		PlanktonReprodT.loadFromFile("PlnkReprod.png", sf::IntRect(0, 0, 20, 20));
		HerbivoreEat.setTexture(HerbivoreEatT);
		HerbivoreMove.setTexture(HerbivoreMoveT);
		HerbivoreReprod.setTexture(HerbivoreReprodT);
		PredatorEat.setTexture(PredatorEatT);
		PredatorMove.setTexture(PredatorMoveT);
		PredatorReprod.setTexture(PredatorReprodT);
		PlanktonMove.setTexture(PlanktonMoveT);
		PlanktonReprod.setTexture(PlanktonReprodT);
	}
	~Sprites(){}

	 sf::Sprite HerbivoreEat;
	 sf::Sprite HerbivoreMove;
	 sf::Sprite HerbivoreReprod;
	 sf::Sprite PredatorEat;
	 sf::Sprite PredatorMove;
	 sf::Sprite PredatorReprod;
	 sf::Sprite PlanktonMove;
	 sf::Sprite PlanktonReprod;
private:
	 sf::Texture HerbivoreEatT;
	 sf::Texture HerbivoreMoveT;
	 sf::Texture HerbivoreReprodT;
	 sf::Texture PredatorEatT;
	 sf::Texture PredatorMoveT;
	 sf::Texture PredatorReprodT;
	 sf::Texture PlanktonMoveT;
	 sf::Texture PlanktonReprodT;
	
};

//C:\\Users\\home\\Source\\Repos\\Aquarium\\aquarium\\

#endif