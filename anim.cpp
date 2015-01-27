//#include <vector>
//#include <string>
#include <cmath> // abs, hypot

//#include "SFML/Graphics.hpp"
#include "anim.hpp"

animFrame::animFrame(int x, int y, int w, int h) {
    rect = sf::IntRect(x, y, w, h);
}

animFrames::animFrames(int type) { // !
    if (type == 1) {
        loadFrames(std::vector<std::string>{"chiisayanagi-d59.png"});
    }
    else {
        loadFrames(std::vector<std::string>{"xp_character.png"});
    }
}

bool animFrames::loadFrames(const std::vector<std::string> &files) {

    bool returnValue = true;

    int leftBorder = 0, width = 0, rightBorder = 0;
    int topBorder = 0, height = 0, bottomBorder = 0;

    width = 32;
    height = 48;

    int column = 4, row = 4;

    if (!texture.loadFromFile(files[0])) return false;

    for (int i = 0; i < row; i++) {
        frames.push_back(std::vector<animFrame>());
        for (int j = 0; j < column; j++) {
            frames.back().push_back(animFrame(
                leftBorder + (j * (leftBorder + width + rightBorder)),
                topBorder + (i * (topBorder + height + bottomBorder)),
                width,
                height));
        }
    }

    return returnValue;
}

animSprite::animSprite(int type) {
    anim = animFrames(type); // !
    setTexture(anim.texture);
    setTextureRect(anim.frames[activeAnim][frameCount].rect);
    setOrigin(16., 40.);
}

void animSprite::resetTimer() {
    animTimer = 0;
}

void animSprite::update(const int delta) {

    if (animate) {

        animTimer += delta;

        if (animTimer > anim.frames[activeAnim][frameCount].delay) {
            frameCount = (++frameCount == (int)anim.frames[activeAnim].size() ? 0 : frameCount); // !
            setTextureRect(anim.frames[activeAnim][frameCount].rect);
            resetTimer();
            //std::cout << anim.frames[frameCount].name << std::endl;
        }

    }

    if (!static_) {

        float smoothFactor = delta / 1000.;// / (1000. / fps);
        //std::cout << delta << " - " << smoothFactor << std::endl;

        if (getPosition() != goal) {

            sf::Vector2f position = getPosition();

            x = goal.x - position.x;
            y = goal.y - position.y;
            path = std::hypot(x, y);
            speed.x = (x / path) * SPEED_X_CONST * smoothFactor;
            speed.y = (y / path) * SPEED_Y_CONST * smoothFactor;
            position.x = (abs(x) < abs(speed.x) ? goal.x : position.x + speed.x);
            position.y = (abs(y) < abs(speed.y) ? goal.y : position.y + speed.y);

            //float pi = 3.14159265;
            float sval = (y / path);
            float cval = (x / path);
            float sr2 = sqrt(2.) / 2.;

            if (sval >= sr2) {
                activeAnim = 0;
            } else if (cval >= sr2) {
                activeAnim = 2;
            } else if (sval <= -sr2) {
                activeAnim = 3;
            } else {
                activeAnim = 1;
            }

            setPosition(position);

            animate = true;

        }
        else {
            setTextureRect(anim.frames[0][0].rect);
            speed.x = 0;
            speed.y = 0;
            animate = false;
        }

    }

}

