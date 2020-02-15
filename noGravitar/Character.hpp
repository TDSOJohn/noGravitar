//
//  Character.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include "Settings.h"

#include "Bullet.hpp"

class Character : public sf::Drawable
{
public:
    Character(const TextureHolder = TextureHolder(), sf::Vector2f = sf::Vector2f());
    ~Character();
    
    bool                operator==(const Bullet&);
    int                 isHit(int);
 
    sf::Vector2f        getPosition()   { return characterSprite.getPosition(); }
    sf::FloatRect       getBounds()     { return characterSprite.getGlobalBounds(); }
    int                 getLife()       { return life; }
    bool                isShooting()    { return shooting; }
    
private:
    bool                shooting;
    int                 life;
    
    sf::Sprite          characterSprite;
    sf::RectangleShape  lifeBar;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(characterSprite);
        target.draw(lifeBar);
    }
};

#endif /* Character_hpp */
