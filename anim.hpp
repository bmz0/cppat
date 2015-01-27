#pragma once
#include <vector>
#include <list>
#include <memory>

#include "SFML/Graphics.hpp"

class animFrame {
public:
    animFrame(int x, int y, int w, int h);
    sf::IntRect rect;
    int delay = 100;
    std::string name;
};

class animFrames {
public:
    animFrames(int type);
    std::string name = "newAnim";
    std::vector<std::vector<animFrame>> frames;
    sf::Texture texture;
    bool loaded = false;
    bool loadFrames(const std::vector<std::string> &files);
};

class animSprite: public sf::Sprite {
public:
    animSprite(int type);
    animFrames anim{0};
    std::string name = "newSprite";
    std::list<std::shared_ptr<animSprite>> inventory;
    int animTimer = 0;
    int activeAnim = 0;
    int frameCount = 0;
    void update(const int delta);
    void resetTimer();
    bool animate = false;
    bool static_ = false;
    sf::Vector2f goal, speed;
    float x, y, path;
    const float SPEED_X_CONST = 112.;
    const float SPEED_Y_CONST = 112.;
};


