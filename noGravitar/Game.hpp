//
//  Game.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "ResourceHolder.hpp"
#include "Overlay.hpp"
#include "SolarSystem.hpp"

class Game
{
public:
    Game(const ResourceHolder<sf::Texture, Textures::ID>& txtrs);
    void                run();
    
private:
    void                processEvents();
    void                render();
    void                youWon();
    void                youLost();
    
private:
Settings::gameStates    gameState;
    int                 score;
    
    const ResourceHolder<sf::Texture, Textures::ID>* textures;
    Overlay             gameOverlay;
    sf::RenderWindow    mainWindow;             //Window & general game loop stuff
    sf::View            mainView;
    SolarSystem*        solarSystem;
    sf::Time            TimePerFrame;
};
#endif /* Game_hpp */
