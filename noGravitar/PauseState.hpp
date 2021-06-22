//
//  PauseState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef PauseState_hpp
#define PauseState_hpp

#include "Core/State.hpp"
#include "GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);
    
    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);
    
    
private:
    sf::Sprite                  mBackgroundSprite;
    sf::Text                    mPausedText;
    GUI::Container              mGUIContainer;
};


#endif /* PauseState_hpp */
