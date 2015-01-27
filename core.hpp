#pragma once
#include <list> // std::list just a list that holds a kind of object.
#include <iostream> // needed for std::cout to write stuff to the terminal
//#include <chrono> // time management in the standard lib
#include <memory> // needed for std::shared_ptr
#include <string> //std::string
#include <deque>

#include "SFML/Graphics.hpp"

//static int average(const std::deque<int> &numbers);

class gameCore {
public:
    /*std::chrono::high_resolution_clock clock;
    std::chrono::milliseconds deltaTime;*/
    sf::Clock clock;
    sf::RenderWindow window;
    sf::View camera;
    bool run();
};

//#include "scene.hpp"
