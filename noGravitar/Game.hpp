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
                        Game(const TextureHolder&);
    void                run();
    
private:
    void                processEvents();
    void                render();
    void                youLost();
    
Settings::gameStates    gameState;
    
private:
    sf::RenderWindow    mainWindow;
    sf::View            mainView;
    TextureHolder       textures;
    SolarSystem         solarSystem;
    sf::Time            TimePerFrame;
};
#endif /* Game_hpp */
