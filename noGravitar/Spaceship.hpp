//
//  Spaceship.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp

#include "ResourceHolder.hpp"
#include "Character.hpp"

class Spaceship : public Character
{
public:
    Spaceship(const ResourceHolder& =ResourceHolder(), Textures::ID =Textures::Spaceship, sf::Vector2f =sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
    
    void                move(sf::Vector2f, bool, bool);             //Move from current position by vector2f passed, bool for shooting and hook movement
    void                move(sf::Vector2f);                         //Move to position passed by vector2f

    sf::FloatRect       getHookBounds()         { return hookSprite.getGlobalBounds(); }
    bool                isGrabbing()            { return grabbing; }
    
private:
    bool                grabbing;
    sf::Sprite          hookSprite;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(characterSprite);
        if(grabbing)
            target.draw(hookSprite);
        target.draw(lifeBar);
    }
};

#endif /* Spaceship_hpp */
