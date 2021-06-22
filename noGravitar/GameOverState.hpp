//
//  GameOverState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 20/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef GameOverState_hpp
#define GameOverState_hpp

#include "Core/State.hpp"
#include "GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState: public State
{
public:
    GameOverState(StateStack& stack, Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    sf::Text            mGameOverText;
    sf::Time            mElapsedTime;
};

#endif /* GameOverState_hpp */
