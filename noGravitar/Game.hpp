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

#include "ResourcePath.hpp"
#include "Settings.h"
#include "SolarSystem.hpp"

class Game
{
public:
                        Game(const TextureHolder& txtrs);
    void                run();
    
private:
    void                processEvents();
    void                render();
    void                youWon();
    void                youLost();
    
private:
Settings::gameStates    gameState;
    
    sf::RenderWindow    mainWindow;             //Window & general game loop stuff
    sf::View            mainView;
const TextureHolder*    textures;
    SolarSystem*        solarSystem;
    sf::Time            TimePerFrame;
    
    sf::Sprite          youLostMessage;
};
#endif /* Game_hpp */
