#include "Game.hpp"

// Init
void Game::initVariables()
{
    this->window = nullptr;
    
    // Game logic
    this->endGame = false;
    this->restartGame = false;
    this->points = 0;
    this->losses = 0;
    this->level = 1;
    this->flySpawnTimerMax = 10.f;
    this->flySpawnTimer = this->flySpawnTimerMax;
    this->maxFlies = 5;
    
    // Splash Screen
    this->started = false;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow(this->videoMode, "Fly Trap", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("assets/Butcherman-Regular.ttf"))
    {
        std::cout << "ERROR: Failed to load font." << std::endl;
    }
}

void Game::initText(const sf::Font &font, sf::Text &text, unsigned int size, sf::Color color, float x, float y)
{
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setPosition(x, y);
        text.setString("None");
}

void Game::initFlies()
{
    this->texture.loadFromFile("assets/fly-2.png");
    this->fly.setTexture(texture);
    this->fly.setScale(0.20f, 0.20f);
}

void Game::initVFT()
{
    this->texture2.loadFromFile("assets/vft-2.png");
    this->vft.setTexture(texture2);
    this->vft.setPosition(this->xPos, this->yPos);
    this->vft.setScale(0.20f, 0.20f);
}

// Constructor/Deconstructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    // Points/losses text
    this->initText(this->font, this->uiText, 24, sf::Color::White, 2.f, 2.f);
    // Level text
    this->initText(this->font, this->levelText, 32, sf::Color::Red, 330.f, 20.f);
    // Restart text
    this->initText(this->font, this->restartText, 24, sf::Color::Yellow, 210.f, 90.f);
    this->initFlies();
    this->initVFT();
    
    // Splash Screen
    // Splash screen text
    this->initText(this->font, this->splashText, 90, sf::Color::Green, 220.f, 200.f);
    // Enter to play text
    this->initText(this->font, this->enterToPlayText, 42, sf::Color::White, 200.f, 420.f);
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

// Functions

void Game::spawnFly()
{
    this->fly.setPosition(
               static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->fly.getTexture()->getSize().x + 100)),
               0.f
    );
    
    // Spawn the fly
    this->flies.push_back(this->fly);
}

void Game::pollEvents()
{
    // Game loop
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
                
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
            default:
                break;
        }
    }
}

void Game::updateFlies()
{
    // Updating the timer for fly spawning
    if (this->flies.size() < this->maxFlies)
    {
        if (this->flySpawnTimer >= this->flySpawnTimerMax)
        {
            // Spawn the fly and reset the timer
            this->spawnFly();
            this->flySpawnTimer = 0.f;
        }
        else
            this->flySpawnTimer += 1.f;
    }
    
    // Move the flies
    for (int i = 0; i < this->flies.size(); i++) {
        
        bool deleted = false;
        
        // Speed of flies
        switch (this->level) {
            case 1: this->flies[i].move(0.f, 1.f); break;
            case 2: this->flies[i].move(0.f, 1.5f); break;
            case 3: this->flies[i].move(0.f, 2.f); break;
            case 4: this->flies[i].move(0.f, 2.5f); break;
            case 5: this->flies[i].move(0.f, 3.f); break;
            case 6: this->flies[i].move(0.f, 3.5f); break;
            case 7: this->flies[i].move(0.f, 4.f); break;
            case 8: this->flies[i].move(0.f, 4.5f); break;
            case 9: this->flies[i].move(0.f, 5.f); break;
            case 10: this->flies[i].move(0.f, 5.5f); break;
            case 11: this->flies[i].move(0.f, 6.f); break;
            case 12: this->flies[i].move(0.f, 6.5f); break;
        }
        
        // Check if fly hits VFT
        if (this->flies[i].getGlobalBounds().intersects(this->vft.getGlobalBounds()))
        {
            deleted = true;
            
            // Gain points
            this->points += 10;
        }
        
        // If the fly goes past the bottom of the screen
        if(this->flies[i].getPosition().y >= this->window->getSize().y - 100)
        {
            deleted = true;
            
            // Track lost flies
            this->losses += 1;
        }
            
        if(deleted)
            this->flies.erase(this->flies.begin() + i);
    }
}

void Game::updateVFT()
{
    if (sf::Event::KeyPressed) {
        if (this->ev.key.code == sf::Keyboard::Left && this->vft.getPosition().x > 0.f) {
            this->vft.move(-5.f, 0);
        }
        
        if (this->ev.key.code == sf::Keyboard::Right && this->vft.getPosition().x < 627.f) {
            this->vft.move(5.f, 0);
        }
    }
}

void Game::updateText(std::string output, sf::Text &text, bool level)
{
    std::stringstream ss;
    ss << output;
    
    text.setString(ss.str());
    
    if (level == true)
    {
        switch (this->points) {
            case 100: this->level = 2; break;
            case 200: this->level = 3; break;
            case 300: this->level = 4; break;
            case 400: this->level = 5; break;
            case 500: this->level = 6; break;
            case 600: this->level = 7; break;
            case 700: this->level = 8; break;
            case 800: this->level = 9; break;
            case 900: this->level = 10; break;
            case 1000: this->level = 11; break;
            case 1100: this->level = 12; break;
        }
    }
}

std::string Game::convert()
{
    std::stringstream ss;
    ss << "Points:  " << this->points << "\n"
    << "Losses:  10";
    
    return ss.str();
    
}

void Game::update()
{
    this->pollEvents();
    
    if (sf::Event::KeyPressed) {
        if (this->ev.key.code == sf::Keyboard::Enter) {
            this->started = true;
        }
    }
    
    if (this->restartGame == false && this->started == true)
    {
        // Points/Losses text
        this->updateText("Points:  " + std::to_string(this->points) + "\n" + "Losses:  " + std::to_string(this->losses), uiText, false);
        // Level text
        this->updateText("Level  " + std::to_string(this->level) + "\n", levelText, true);
        // Restart text
        this->updateText("", restartText, false);
        this->updateFlies();
        this->updateVFT();
    }
    
    if (this->losses == 10)
    {
        this->restartGame = true;
        this->levelText.setString("GAME OVER");
        this->levelText.setFillColor(sf::Color::Red);
        this->restartText.setString("Press 'Y' to restart or 'N' to quit.");
        this->uiText.setString(this->convert());
        
        if (sf::Event::KeyPressed) {
            if (this->ev.key.code == sf::Keyboard::Y) {
                this->restart();
            }
            
            if (this->ev.key.code == sf::Keyboard::N) {
                this->endGame = true;
            }
        }
    }
    
    // Splash Screen
    // Splash title text
    this->updateText("Fly Trap", splashText, false);
    // Enter to play text
    this->updateText("Press Enter to Play", enterToPlayText, false);
}

void Game::renderText(sf::RenderTarget &target, sf::Text &text)
{
    target.draw(text);
}


void Game::renderFlies(sf::RenderTarget& target)
{
    // Rendering all the flies
    for (auto &f : this->flies) {
        target.draw(f);
    }
}

void Game::renderVFT()
{
    this->window->draw(vft);
}

void Game::render()
{
    this->window->clear();
    
    if (this->started == true)
    {
        // Background
        this->bgTexture.loadFromFile("assets/background.png");
        this->background.setTexture(bgTexture);
        this->background.setPosition(0, 0);
        this->background.setScale(0.47f, 0.47f);
        this->window->draw(background);
        
        // Draw game objects
        this->renderFlies(*this->window);
        this->renderVFT();
        
        // Points/losses text
        this->renderText(*this->window, this->uiText);
        // Level text
        this->renderText(*this->window, this->levelText);
        // Restart text
        this->renderText(*this->window, this->restartText);
    } else {
        // Splash Screen
        // Title text
        this->renderText(*this->window, this->splashText);
        // Press Enter to play text
        this->renderText(*this->window, this->enterToPlayText);
    }
    
    this->window->display();
}

void Game::restart()
{
    this->endGame = false;
    this->restartGame = false;
    this->points = 0;
    this->losses = 0;
    this->level = 1;
    this->flySpawnTimerMax = 10.f;
    this->flySpawnTimer = this->flySpawnTimerMax;
    this->maxFlies = 5;
    
    this->flies.clear();
    
    this->render();
}
