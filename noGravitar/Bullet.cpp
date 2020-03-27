//
//  Bullet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture& texture, const entitySettings eSettings, sf::Vector2f position, float rot)
                                    : directionVector(0.f, 0.f), GameEntity(texture, eSettings, position, rot)
{
    directionVector = sf::Vector2f(settings.speed*std::sin((180-settings.rotation)*PI/180),
                                   settings.speed*std::cos((180-settings.rotation)*PI/180));
}

bool Bullet::move(const sf::Time& expTime)
{
    this->setPosition(this->getPosition() + (directionVector*expTime.asSeconds()));
    
    return(this->getPosition().x > 0 &&
           this->getPosition().x < Settings::MAP_X &&
           this->getPosition().y > 0 &&
           this->getPosition().y < Settings::MAP_Y);
}
