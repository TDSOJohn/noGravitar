//
//  Bullet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture& bulletTexture, sf::Vector2f position, int dam, float rot) : bulletSprite(bulletTexture), directionVector(0.f, 0.f), settings(Settings::BULLET)
{
    settings.rotation = 180.f - rot;
    settings.damage = dam;
    bulletSprite.setOrigin(Settings::ICONS_DIM/8, Settings::ICONS_DIM/4);
    bulletSprite.setPosition(position);
    bulletSprite.setRotation(settings.rotation*(-1));
    
    directionVector = sf::Vector2f(settings.speed*std::sin(settings.rotation*PI/180),
                                   settings.speed*std::cos(settings.rotation*PI/180));
}

bool Bullet::move(const sf::Time& expTime)
{
    bulletSprite.move(directionVector*expTime.asSeconds());
    
    return(bulletSprite.getPosition().x > 0 &&
           bulletSprite.getPosition().x < Settings::MAP_X &&
           bulletSprite.getPosition().y > 0 &&
           bulletSprite.getPosition().y < Settings::MAP_Y);
}
