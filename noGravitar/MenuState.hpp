//
//  MenuState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 27/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef MenuState_hpp
#define MenuState_hpp


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Core/State.hpp"
#include "GUI/Container.hpp"


class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);
    
    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);
        
private:
    sf::Sprite                  Bar_1;
    sf::Sprite                  Bar_2;

    GUI::Container              mGUIContainer;
};

#endif /* MenuState_hpp */
