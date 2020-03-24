//
//  Enemy.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 04/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp


#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "ResourceHolder.hpp"
#include "Character.hpp"

class Enemy : public Character      //Character class inherits almost everything from Character
{
public:
    using               Character::Character;
    float               getRotation();
    Textures::ID        getBulletID();

private:
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(entitySprite);
        target.draw(Character::lifeBar);
    }
};

#endif /* Enemy_hpp */

