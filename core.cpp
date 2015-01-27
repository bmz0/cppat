#include <ctime> //srand(time(0));
#include <algorithm>

//#include "SFML/Graphics.hpp"

//#include "anim.hpp"
#include "core.hpp"
#include "scene.hpp"

const unsigned int SCREEN_WIDTH = 256;
const unsigned int SCREEN_HEIGHT = 256;

const unsigned int CAMERA_WIDTH = 256;
const unsigned int CAMERA_HEIGHT = 256;
const unsigned int CAMERA_CENTER_X = 128;
const unsigned int CAMERA_CENTER_Y = 128;

static int average(const std::deque<int> &numbers) {
    int sum = 0;
    for (int i = 0; i < (int)numbers.size(); sum += numbers[i++]);
    return (sum / (int)numbers.size());
}

static void setupScene(std::shared_ptr<scene> &thisScene, int type) {
    
    thisScene->textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    thisScene->textures.back()->loadFromFile("key-icon.png");
    thisScene->addSprite(sf::Vector2f(32 + (rand() % 200), 32 + (rand() % 480)));
    thisScene->sprites.back()->setTexture(*thisScene->textures.back(), true);
    thisScene->sprites.back()->name = "key";
    thisScene->key = thisScene->sprites.back();

    thisScene->textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    thisScene->textures.back()->loadFromFile("door-icon.png");
    thisScene->addSprite(sf::Vector2f(288 + (rand() % 208), 16 + (rand() % 496)));
    thisScene->sprites.back()->setTexture(*thisScene->textures.back().get(), true);
    thisScene->sprites.back()->name = "door";
    thisScene->door = thisScene->sprites.back();
    
    sf::Vector2f position = sf::Vector2f(256., 256.);
    thisScene->sprites.push_back(std::shared_ptr<animSprite>(new animSprite(type)));
    thisScene->sprites.back()->setPosition(position);
    thisScene->sprites.back()->goal = position;
    
}

bool gameCore::run() {

    srand(time(0));
    
    bool changeScene = false;

    sf::Event event;
    sf::Time deltaTime;
    std::shared_ptr<scene> activeScene;

    window.create(sf::VideoMode(256, 256), "animation test");

    camera.setViewport(sf::FloatRect(0, 0, 1, 1));
    camera.setCenter(128, 128);
    camera.setSize(256, 256);
    //camera.rotate(90);
    //camera.zoom(.5);
    window.setView(camera);

    int fps = 30;
    std::deque<int> lastFrames;
    lastFrames.resize(10, 1000/fps);
    int updateTime;

    window.setFramerateLimit(fps);

    /*sf::Shader shader;
    shader.loadFromFile("colorkey.frag", sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.setParameter("colorkey", sf::Color(255, 0, 255));*/

    //window.setVerticalSyncEnabled(true);
    window.clear(sf::Color::Black);
    window.display();

    //std::chrono::time_point<std::chrono::high_resolution_clock> oldTime = clock.now();
    sf::Time oldTime = clock.getElapsedTime();

    // pre-construct test scenes
    std::shared_ptr<scene> scene1, scene2;
    scene1 = std::shared_ptr<scene>(new scene());
    scene2 = std::shared_ptr<scene>(new scene());
    scene1->init(0);
    scene2->init(1);

    setupScene(scene1, 0);

    bool activeFlag = 1;

    activeScene = scene1;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                   window.close();
                }
                else if (event.key.code == sf::Keyboard::S) {
                    activeFlag = !activeFlag;
                    changeScene = true;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    camera.rotate(90);
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    camera.rotate(-90);
                }
            }
            else {
                activeScene->handleEvent(event); //(this, event);
            }

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!activeScene->sprites.empty()) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                //std::cout << position.x << ":" << position.y << std::endl;
                if (!((position.x < 0) || (position.y < 0)
                    ||(position.x > (int)window.getSize().x) || (position.y > (int)window.getSize().y)))
                    activeScene->sprites.back()->goal = window.mapPixelToCoords(position);
            }
        }

        //deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - oldTime);
        //oldTime = clock.now();
        deltaTime = clock.getElapsedTime() - oldTime;
        oldTime = clock.getElapsedTime();

        updateTime = (average(lastFrames) < (deltaTime.asMilliseconds() / 2) ? average(lastFrames) : deltaTime.asMilliseconds());
        lastFrames.pop_front();
        lastFrames.push_back(deltaTime.asMilliseconds());

        //std::cout << average(lastFrames) << std::endl;

        //window.clear(sf::Color::Black);
        //window.setView(window.getDefaultView());
        //window.clear();
        
        if (activeScene->draw(window, updateTime)) {
            activeFlag = !activeFlag;
            changeScene = true;
        }

        window.setView(camera);

        if (!activeScene->sprites.empty()) {
            sf::Vector2f center = activeScene->sprites.back()->getPosition();
            if (center.x > (512 - 128)) center.x = (512 - 128);
            if (center.x < (128)) center.x = (128);
            if (center.y > (512 - 128)) center.y = (512 - 128);
            if (center.y < (128)) center.y = (128);
            camera.setCenter(center);
        }

        window.setView(camera);

        window.display();
        
        if (changeScene) {
            if (activeFlag) {
                scene1->sprites.clear();
                setupScene(scene1, 0);
                activeScene = scene1;
            }
            else {
                scene2->sprites.clear();
                setupScene(scene2, 1);
                activeScene = scene2;
            }
            changeScene = false;
        }

    }

    return true;

}
