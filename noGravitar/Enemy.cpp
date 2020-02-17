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
        return (settings.rotation + rand()%40 -10);
    else
        return settings.rotation;
}
