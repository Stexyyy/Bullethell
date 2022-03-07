#include "bullet.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include<math.h>
#include<iostream>
using namespace std;

//default constructor
bullet::bullet() {
	xpos = 0;
	ypos = 0;
	alive = false;
	radius = 10;
	angle = 0;
}


//desturctor
bullet::~bullet() {}

//paramemeterized constructor with SFML image
bullet::bullet(int x, int y, sf::Sprite sprite, float a) {
	xpos = x;
	ypos = y;
	alive = false;
	image = sprite;
	radius = 10;
	angle = a;
}

//Parameterized constructor without image (not used, code would need to be asjusted)
bullet::bullet(int x, int y, float a) {
	xpos = x;
	ypos = y;
	alive = false;
	radius = 10;
	angle = a;
}

void bullet::move() {
	ypos -= 5; //simply move the bullet up when called
	cout << "inside move function";
}

//we pass a pointer to the SFML game screen here // so the function knows where to draw it!
void bullet::draw(sf::RenderWindow& window) {
	if (alive) { // don't draw dead bullets
		image.setPosition(xpos, ypos);
		window.draw(image); //draw to gamescreen
	}
}

void bullet::kill() {
	alive = false;
}

bool bullet::offScreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}

void bullet::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool bullet::isAlive() {
	return alive;
}

bool bullet::collide(double x, double y) {
	if (sqrt((x - xpos) * (x - xpos) + (y - ypos) * (y - ypos)) < 32) { //circular collision (distance formula)

		return true;
	}
	else
		return false;
}
int bullet::getx() {
	return xpos;
}
int bullet::gety() {
	return ypos;
}

void bullet::move2() {
	radius = 10;
	angle += .1;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
}

void bullet::move3() {
	radius = 10;
	angle += .2;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 3;
	ypos = ypos + sin(angle) * (radius) / 3 + 1;
}
