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

class Spaceship : public sf::Drawable
{
public:
    Spaceship(const ResourceHolder& =ResourceHolder(), sf::Vector2f =sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
    
    bool                operator==(const Bullet&);                  //Operator == checks if spaceship is hitting the bullet
    void                move(sf::Vector2f, bool, bool);             //Move from current position by vector2f passed, bool for shooting and hook movement
    void                move(sf::Vector2f);                         //Move to position passed by vector2f
    int                 isHit(int);                                 //Argument is damage. Returns updated life. If 0, spaceship is dead
    
    sf::Vector2f        getPosition()           { return spaceshipSprite.getPosition(); }
    sf::FloatRect       getBounds()             { return spaceshipSprite.getGlobalBounds(); }
    sf::FloatRect       getHookBounds()         { return hookSprite.getGlobalBounds(); }
    int                 getLife()               { return life; }
    bool                isShooting()            { return shooting; }
    bool                isGrabbing()            { return grabbing; }
    
private:
    bool                shooting;
    bool                grabbing;
    int                 life;

    sf::Sprite          spaceshipSprite;
    sf::RectangleShape  lifeBar;
    sf::Sprite          hookSprite;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(spaceshipSprite);
        if(grabbing)
            target.draw(hookSprite);
        target.draw(lifeBar);
    }
};

#endif /* Spaceship_hpp */
