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


#include "ResourceHolder.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "StateStack.hpp"



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
    sf::RenderWindow    mWindow;
    
    Player              mPlayer;
    
    TextureHolder       mTextures;
    FontHolder          mFonts;
    sf::Text            mStatisticsText;
    
    StateStack          mStateStack;
    
    static const sf::Time
                        TimePerFrame;
};
#endif /* Game_hpp */
