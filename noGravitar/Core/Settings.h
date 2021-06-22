//
//  Settings.h
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Settings_h
#define Settings_h


#include <SFML/System/Vector2.hpp>



#define PI 3.14159265
/*
 Fire rate is in shoots/second
 
 Xs, Ys and DIMs are in pixels
 Fuel rate is in fuel(life)/second
 */

namespace Settings
{
    const unsigned int      MAP_X = 1920;
    const unsigned int      MAP_Y = 1200;
    
    const unsigned int      VIEW_X = 1920;
    const unsigned int      VIEW_Y = 1200;
    
    const unsigned short    ICONS_DIM = 64;
    
    const unsigned short    PLANETS = 3;
    
    const unsigned short    GROUND_POINTS = 11;
    
    const unsigned int      ENEMY_SCORE = 100;
    const unsigned int      PLANET_SCORE = 1000;
    const unsigned int      SOLARSYSTEM_SCORE = 2500;
    
    const unsigned int      SPACESHIP_FUEL = 50;
    const unsigned int      HOOK_SPEED = 450;
}

#endif /* Settings_h */
