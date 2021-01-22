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
    enum                ID {
                                ssBackground,
                                pBackground,
                                Planet,
                                Raptor,
                                Eagle,
                                Hook,
                                Fuel,
                                Enemy_1,
                                Enemy_2,
                                Bullet_1,
                                Bullet_2,
                                Bullet_3,
                                Won,
                                Lost
                            };
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
    
    const unsigned int      VIEW_X = 1280;
    const unsigned int      VIEW_Y = 854;
    
    const unsigned short    ICONS_DIM = 64;
    
    const unsigned short    PLANETS = 3;
    
    const unsigned short    GROUND_POINTS = 11;
    
    const unsigned int      ENEMY_SCORE = 100;
    const unsigned int      PLANET_SCORE = 1000;
    const unsigned int      SOLARSYSTEM_SCORE = 2500;
    
    const unsigned int      SPACESHIP_FUEL = 50;
    const unsigned int      HOOK_SPEED = 450;
    
    const entitySettings    SPACESHIP = { Textures::Eagle,      70,   750,    9,      8,      0 };
    const entitySettings    ENEMY_1   =   { Textures::Enemy_1,    70,   0,      2.7,    3,      0 };
    const entitySettings    ENEMY_2   =   { Textures::Enemy_2,    50,   0,      0.6,    4,      0 };
    
    //  Rotation is default for spaceship orientation, aka 180.f
    const entitySettings    BULLET_SPACESHIP
                                      =  { Textures::Bullet_1,   0,    730,    0,      5,      180.f};
    const entitySettings    BULLET_2a =  { Textures::Bullet_2,   0,    550,    0,      3,      25.f };
    const entitySettings    BULLET_2b =  { Textures::Bullet_2,   0,    550,    0,      3,      -25.f};
    const entitySettings    BULLET_3  =  { Textures::Bullet_3,   0,    950,    0,      8,      0 };
}

#endif /* Settings_h */
