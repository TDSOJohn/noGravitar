//
//  Character.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "GameEntity.hpp"
#include "Bullet.hpp"

class Character : public GameEntity
{
public:
    Character(const sf::Texture&  =sf::Texture(), const entitySettings& =entitySettings(),
              const sf::Vector2f& =sf::Vector2f(), float =0.f);
    
    bool                operator==(const Bullet&); //return 1 if bounds intersect
    int                 isHit(int); //return updated life
 
    int                 getLife()       { return settings.life; }
    int                 getDamage()     { return settings.damage; }
    bool                isShooting()    { return shooting; }
    
protected:
    bool                shooting;
    
    sf::RectangleShape  lifeBar;

};

#endif /* Character_hpp */
