//
//  TitleState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef TitleState_hpp
#define TitleState_hpp


#include "State.hpp"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>



class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);
    
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);
    
    
private:
    sf::Sprite          Bar_1, Bar_2, Title;
    sf::Text            mText;
    
    bool                mShowText;
    sf::Time            mTextEffectTime;
};


#endif /* TitleState_hpp */
