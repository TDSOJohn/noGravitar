//
//  Enemy.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 04/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Enemy.hpp"

float Enemy::getRotation()
{
    if(settings.entityType == Textures::Enemy_1)
        return (settings.rotation + rand()%50 -25);
    else
        return settings.rotation;
}

Textures::ID Enemy::getBulletID()
{
    if(settings.entityType == Textures::Enemy_1)
        return Textures::Bullet_1;
    else
        return Textures::Bullet_2;
}
