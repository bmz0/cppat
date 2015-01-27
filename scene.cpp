//#include <list>

//#include "SFML/Graphics.hpp"

//#include "core.hpp"
#include "anim.hpp"
#include "scene.hpp"

bool scene::init(int tmpType) {

    if (tmpType == 1) {
        backgroundTexture.loadFromFile("bg512_2.png"); // power of 2
    }
    else {
        backgroundTexture.loadFromFile("bg512.png"); // power of 2
    }
    //backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    //background.setTextureRect(sf::IntRect(0, 0, 256, 256));
    type = tmpType;
    return true;

}

scene::~scene() {
    sprites.clear();
}

void scene::addSprite(sf::Vector2f position) {
    sprites.push_back(std::shared_ptr<animSprite>(new animSprite(2)));
    sprites.back()->setPosition(position);
    sprites.back()->static_ = true;
}

bool scene::draw(sf::RenderWindow &window, int updateTime) {

    bool returnValue = false;
    //sf::View mainView = window.getView();

    window.draw(background);

    if (key) {

        for (std::shared_ptr<animSprite> &thisSprite: sprites) {
            if (thisSprite == key) continue;
            if (key->getGlobalBounds().intersects(thisSprite->getGlobalBounds())) {
                //std::cout << key->name << " - " << thisSprite->name << std::endl;
                thisSprite->inventory.push_back(key);
                sprites.remove(key);
                key->setPosition(sf::Vector2f(32, 264));
                break;
            }
        }
        
    }

    if (door) {
        for (std::shared_ptr<animSprite> &thisSprite: sprites) {
           for (std::shared_ptr<animSprite> &item: thisSprite->inventory) {
                if (item->name == "key") {
                    if (door->getGlobalBounds().intersects(thisSprite->getGlobalBounds())) {
                        returnValue = true;
                        break;
                    }
                }
            }

        }
    }

    for (std::shared_ptr<animSprite> &thisSprite: sprites) {
        thisSprite->update(updateTime); // deltaTime.count()
        window.draw(*thisSprite);//, &shader);
    }
    
    if (!sprites.back()->inventory.empty()) {
        window.setView(window.getDefaultView());
        for (std::shared_ptr<animSprite> &thisSprite: sprites.back()->inventory) {
            thisSprite->update(updateTime); // deltaTime.count()
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(20, 20));
            rectangle.setFillColor(sf::Color(64, 64, 64));
            rectangle.setOutlineColor(sf::Color(192, 192, 192));
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(14, 222);
            window.draw(rectangle);
            window.draw(*thisSprite);//, &shader);
        }
    }
        
    return returnValue;

}

//void scene::handleEvent(const gameCore *game, const sf::Event &event) {
void scene::handleEvent(const sf::Event &event) {
    
    if (event.type == sf::Event::KeyPressed) {
        /*if (event.key.code == sf::Keyboard::Space) {
            sprites.clear();
        }*/
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        //std::unique_ptr<sf::RenderWindow> window = &(game.window);
        /*if (event.mouseButton.button == sf::Mouse::Left) {

        }*/
        /*if (event.mouseButton.button == sf::Mouse::Middle) {
            sprites.remove_if([&game, &event](std::shared_ptr<animSprite> &thisSprite) {
                sf::Vector2f position = game->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                return (thisSprite->getGlobalBounds().contains(position)) && (thisSprite->name != "key");
            });
        }
        if (event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2f position = game->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            sprites.push_back(std::shared_ptr<animSprite>(new animSprite(this->type)));
            sprites.back()->setPosition(position);
            sprites.back()->goal = position;
            //game->camera.setCenter(position);
        }*/
    }

}
