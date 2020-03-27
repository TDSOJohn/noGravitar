//
//  Bullet.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
// Costruttore di copia t(const t& oggetto);

#ifndef Bullet_hpp
#define Bullet_hpp

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "GameEntity.hpp"
#include "ResourceHolder.hpp"

class Bullet : public GameEntity
{
public:
    Bullet(const sf::Texture& =sf::Texture(), entitySettings =entitySettings(), sf::Vector2f =sf::Vector2f(), float =0.f); //int is damage, float is rotation angle

    bool                move(const sf::Time& = sf::Time());                                 //Return 0 if bullet no longer inside map coordinates
    int                 getDamage() { return settings.damage; }

private:
    sf::Vector2f        directionVector;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *=getTransform();
        target.draw(entitySprite, states);
    }
};

#endif /* Bullet_hpp */
