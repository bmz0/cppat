/*

  This is a simple program to test animSprite and the timing function related to it.
  The program starts in main(), and as with these kind of game-like programs in general
  they have a loop after a simple setup that handles input then draws stuff.

*/

//#include "SFML/Graphics.hpp"

#include "core.hpp"
//#include "scene.hpp"

int main() { //int argc, char** args) {

    gameCore game;

    game.run();

  /*  if (!sf::Shader::isAvailable()) {
        std::cerr << "Error: shaders not supported by system!";
        return EXIT_FAILURE;
    }*/

    return EXIT_SUCCESS;

}

