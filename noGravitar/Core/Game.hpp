//
//  Game.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "Player.hpp"
#include "World.hpp"
#include "SolarSystem.hpp"



class Game : private sf::NonCopyable
{
public:
                        Game();
    void                run();
    
private:
    void                processInput();
    void                update(sf::Time elapsedTime);
    void                render();
    void                updateStatistics(sf::Time elapsedTime);
    
private:
    Settings::gameStates
                        gameState;
    int                 score;
    
    sf::RenderWindow    mWindow;
    
    World               mWorld;
    Player              mPlayer;
    
    sf::Font            mFont;
    sf::Text            mStatisticsText;
    
    static const sf::Time
                        TimePerFrame;
};
#endif /* Game_hpp */
