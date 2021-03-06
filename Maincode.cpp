#include<iostream>
#include<vector>
#include "SFML/Graphics.hpp"
#include"globals.h"
#include"missiles.h"
using namespace std;

//enum DIRECTIONS { LEFT, RIGHT, UP, DOWN, SPACE }; //left is 0, right is 1, up is 2, down is 3

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(800, 800), "Bullet Hell"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS



    //player setup------------------------------------------------
    sf::Texture ship;
    ship.loadFromFile("ship.png");
    sf::IntRect playerImg(0, 0, 30, 30); //select portion of image to draw (our ship is 30x30)
    sf::Sprite player(ship, playerImg);
    // player.setTexture(ship); //use this instead of 2 lines above for static images
    int xpos = 400;
    int ypos = 700;
    int vx = 0;
    int vy = 0;
    int ticker = 60;
    int frameNum = 0;
    int direction = RIGHT;
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false, false };


    //missile (the things the player shoots) setup-----------------------
    int justShot = 0;
    //set up variables for missle image
    sf::Texture MissileImg;
    MissileImg.loadFromFile("missile.png");
    sf::Sprite MissilePic;
    MissilePic.setTexture(MissileImg);

    //vector to hold missiles
    vector<missile*> missiles; // creates vector of class missile pointers
    vector<missile*>::iterator iter2; // creates an iterator to walk through our missiles vector
    for (int i = 0; i < 5; i++) {
        missile* newMissile = new missile(xpos, ypos, MissilePic);
        missiles.push_back(newMissile);
    }

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();

            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                keys[SPACE] = true;
            }
            else keys[SPACE] = false;


        }//end event loop---------------------------------------------------------------

        justShot++; //increment ticker
        if (keys[SPACE] == true) {
            for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
                if (((*iter2)->isAlive()) == false && justShot > 5) { //only shoot dead missiles, add in pause
                    (*iter2)->shoot(xpos, ypos); //shoot the thing the iterator is pointing to
                    justShot = 0; //reset ticker
                }


            }

        }


        //move missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            
                (*iter2)->move();
            cout << "moving missiles!";
        }

        //cull the missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->offScreen())
                (*iter2)->kill();
        }

        //move ship
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;
        else vx = 0;

        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;
        else vy = 0;






        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        //animation---------------------------------------------------
        ticker += 1;

        if (ticker % 10 == 0)
            frameNum += 1;

        if (frameNum > 4)
            frameNum = 0;

        if (direction == RIGHT) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, 30, 30);
        }
        else if (direction == LEFT) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, -30, 30);
            cout << "left" << frameNum + 5;
        }
        else {
            playerImg = sf::IntRect(frameNum * 32, 0, 30, 30);
        }




        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        //draw missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            (*iter2)->draw(screen);
        }

        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
