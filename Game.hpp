#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

class Game
{
    
private:
    // Private variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    
    // Font
    sf::Font font;
    
    // Text
    sf::Text uiText;
    sf::Text levelText;
    sf::Text restartText;
    
    // Splash Screen
    bool started;
    sf::Text splashText;
    sf::Text enterToPlayText;
    
    // Game logic
    bool endGame;
    bool restartGame;
    int points;
    int losses;
    int level;
    float flySpawnTimer;
    float flySpawnTimerMax;
    int maxFlies;
    
    // VFT Position
    float xPos = 300.f;
    float yPos = 380.f;
    
    // Game objects
    sf::Texture texture;
    sf::Sprite fly;
    std::vector<sf::Sprite> flies;
    
    sf::Texture texture2;
    sf::Sprite vft;
    
    sf::Texture bgTexture;
    sf::Sprite background;
    
    // Private init functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText(const sf::Font &font, sf::Text &text, unsigned int size, sf::Color color, float x, float y);
    void initFlies();
    void initVFT();

public:
    // Constructor/Deconstructor
    Game();
    virtual ~Game();
    
    // Accessors
    const bool running() const;
    const bool getEndGame() const;
    
    // Functions
    void spawnFly();
    void pollEvents();
    void updateFlies();
    void updateVFT();
    
    void updateText(std::string output, sf::Text &text, bool level);
    
    void update();
    
    void renderText(sf::RenderTarget& target, sf::Text &text);
    
    void renderFlies(sf::RenderTarget& target);
    void renderVFT();
    void render();
    void restart();
    
    // string convert
    std::string convert();
};

#endif /* Game_hpp */
