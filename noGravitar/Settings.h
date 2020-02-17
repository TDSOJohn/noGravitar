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
#include <SFML/graphics.hpp>

#include "ResourcePath.hpp"

#define PI 3.14159265
/*
    Fire rate is in shoots/second
    Speed is in pixels/second
    Xs, Ys and DIMs are in pixels
    Fuel rate is in fuel(life)/second
 */

struct    characterSettings
{
    const unsigned int      LIFE;
    const unsigned int      SPEED;
    const float             FIRERATE;
    const unsigned short    DAMAGE;
};

namespace Settings
{
    
    enum                    gameStates { Lost, Play, Won, Pause };
    
    const unsigned int      MAP_X = 1920;
    const unsigned int      MAP_Y = 1200;
    
    const unsigned int      VIEW_X = 800;
    const unsigned int      VIEW_Y = 640;
    
    const unsigned short    ICONS_DIM = 64;
    
    const unsigned short    PLANETS = 3;
    
    const unsigned short    GROUND_POINTS = 11;
    const unsigned short    FUEL_POINTS = 4;

    const unsigned int      BULLET_SPEED = 850;

    const unsigned int      HOOK_SPEED = 450;
    
    const characterSettings SPACESHIP = { 50, 750, 10, 10 };
    const characterSettings ENEMY_1 = { 50, 0, 1.5, 5 };
    const characterSettings ENEMY_2 = { 70, 0, 1.5, 3 };
}

#endif /* Settings_h */
