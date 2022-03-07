#pragma once
#pragma once
#include "globals.h"
#include "SFML/Graphics.hpp"

class bullet {
private:
	int xpos;
	int ypos;
	bool alive;
	sf::Sprite image;
	float angle;
	float radius;
public:
	bullet(); //default constructor
	~bullet(); //destructor
	bullet(int x, int y, sf::Sprite sprite, float a);
	bullet(int x, int y, float a);
	void move();
	void move2();
	void move3();
	void draw(sf::RenderWindow& window);
	void kill();
	bool offScreen();
	void shoot(int x, int y);
	bool isAlive();
	bool collide(double x, double y);
	int getx();
	int gety();






};
