//
//  Bullet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture& texture, entitySettings eSettings, sf::Vector2f position) :
            GameEntity(texture, eSettings, position)
{
    settings.rotation -= 180.f;
    this->setRotation(settings.rotation*(-1));
    
    directionVector = sf::Vector2f(settings.speed*std::sin(settings.rotation*PI/180),
                                   settings.speed*std::cos(settings.rotation*PI/180));
}

bool Bullet::move(const sf::Time& expTime)
{
    entitySprite.move(directionVector*expTime.asSeconds());
    
    return(entitySprite.getPosition().x > 0 &&
           entitySprite.getPosition().x < Settings::MAP_X &&
           entitySprite.getPosition().y > 0 &&
           entitySprite.getPosition().y < Settings::MAP_Y);
}
