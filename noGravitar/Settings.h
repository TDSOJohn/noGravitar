//
//  Settings.h
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Settings_h
#define Settings_h

#define PI 3.14159265
/*
    Fire rate is in shoots/second
    Speed is in pixels/second
    Xs, Ys and DIMs are in pixels
    Fuel rate is in fuel(life)/second
 */

namespace Textures
{
    enum                ID { ssBackground, pBackground, Planet, Spaceship, Hook, Fuel, Enemy_1, Enemy_2, Bullet_1, Bullet_2, Bullet_3, Won, Lost };
}

struct    entitySettings
{
    Textures::ID            entityType;
    int                     life;
    unsigned int            speed;
    float                   firerate;
    unsigned short          damage;
    float                   rotation;
    
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
    
    const entitySettings    SPACESHIP = { Textures::Spaceship,  50,   750,    9,      8,      0 };
    const entitySettings    ENEMY_1 =   { Textures::Enemy_1,    70,   0,      2.1,    3,      0 };
    const entitySettings    ENEMY_2 =   { Textures::Enemy_2,    50,   0,      1,      5,      0 };
    const entitySettings    BULLET_1 =  { Textures::Bullet_1,   0,    850,    0,      5,      0 };
    const entitySettings    BULLET_2 =  { Textures::Bullet_2,   0,    550,    0,      3,      0 };
    const entitySettings    BULLET_3 =  { Textures::Bullet_3,   0,    900,    0,      8,      0 };
}

#endif /* Settings_h */
