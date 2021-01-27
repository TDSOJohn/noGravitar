//
//  GameState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp


#include "Core/State.hpp"
#include "World.hpp"
#include "Player.hpp"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>



class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);
    
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);
    
    
private:
    World                mWorld;
    Player&                mPlayer;
};

#endif /* GameState_hpp */
