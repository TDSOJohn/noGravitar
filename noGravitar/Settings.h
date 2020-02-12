//
//  Settings.h
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Settings_h
#define Settings_h

#include <iostream>
#include <cmath>

#include "TextureHolder.hpp"

#define PI 3.14159265
/*
    Fire rate is in shoots/second
    Speed is in pixels/second
    Xs, Ys and DIMs are in pixels
    Fuel rate is in fuel(life)/second
 */

namespace Settings
{
    enum                    gameStates { Play, Pause, Lost };
    
    const unsigned int      MAP_X = 1920;
    const unsigned int      MAP_Y = 1200;
    
    const unsigned int      VIEW_X = 800;
    const unsigned int      VIEW_Y = 640;
    
    const unsigned short    ICONS_DIM = 64;
    
    const unsigned short    PLANETS = 8;
    
    const unsigned short    GROUND_POINTS = 11;
    const unsigned short    FUEL_POINTS = 4;

    const unsigned int      BULLET_SPEED = 750;

    const unsigned int      SPACESHIP_SPEED = 550;
    const unsigned int      SPACESHIP_LIFE = 50;
    const float             SPACESHIP_FIRERATE = 10;
    const unsigned short    SPACESHIP_DAMAGE = 10;
    const unsigned int      SPACESHIP_FUEL_RATE = 1;
    
    const unsigned int      HOOK_SPEED = 450;

    const unsigned short    ENEMY_LIFE = 50;
    const float             ENEMY_FIRERATE = 1.3;
    const unsigned short    ENEMY_DAMAGE = 4;
}

#endif /* Settings_h */
