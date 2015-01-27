#pragma once
#include <list>
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"

#include "core.hpp"
#include "anim.hpp"

class scene {
    int type = 0;
public:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    std::list<std::shared_ptr<animSprite>> sprites;
    std::list<std::shared_ptr<sf::Texture>> textures;
    std::shared_ptr<animSprite> key;
    std::shared_ptr<animSprite> door;
    std::vector<std::list<std::weak_ptr<animSprite>>> layers;
    bool draw(sf::RenderWindow &window, int updateTime);
    void addSprite(sf::Vector2f position);
    void handleEvent(const sf::Event &event);
    //void handleEvent(const gameCore *game, const sf::Event &event);
    bool init(int tmpType);
    ~scene();
};
