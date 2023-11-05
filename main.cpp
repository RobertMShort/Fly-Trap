#include "Game.hpp"

int main(int argc, const char * argv[]) {
    
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));
    
    // Init Game
    Game game;
    
    // Game loop
    while (game.running() && !game.getEndGame()) {
       
        // Update
        game.update();
        
        // Render
        game.render();
    }
}
