//
//  Game.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "ResourceHolder.hpp"
#include "../ResourceIdentifiers.hpp"
#include "Player.hpp"
#include "StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Game : private sf::NonCopyable
{
public:
                        Game();
    void                run();
    
private:
    void                processInput();
    void                update(sf::Time dt);
    void                render();
    
    void                updateStatistics(sf::Time dt);
    void                registerStates();
    
private:    
    static const sf::Time
                        TimePerFrame;

    sf::RenderWindow    mWindow;
    TextureHolder       mTextures;
    FontHolder          mFonts;
    
    Player              mPlayer;
    
    StateStack          mStateStack;

    sf::Text            mStatisticsText;
    sf::Time            mStatisticsUpdateTime;
    std::size_t         mStatisticsNumFrames;
};
#endif /* Game_hpp */
