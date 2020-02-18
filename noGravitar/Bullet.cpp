//
//  Bullet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture& bulletTexture, sf::Vector2f position, Textures::ID bulletID, float rot) : bulletSprite(bulletTexture), directionVector(0.f, 0.f)
{
    if(bulletID == Textures::Bullet_1)
        settings = Settings::BULLET_1;
    else if(bulletID == Textures::Bullet_2)
        settings = Settings::BULLET_2;
    else
        settings = Settings::BULLET_3;
    
    settings.rotation = 180.f - rot;
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
