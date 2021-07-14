//
//  DataTables.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 10/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef DataTables_hpp
#define DataTables_hpp


#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class Spaceship;


struct Direction
{
    Direction(float angle, float distance):
        angle(angle),
        distance(distance)
    {}
    
    float angle;
    float distance;
};

struct SpaceshipData
{
    int                     life;
    float                   speed;
    Textures::ID            texture;
    sf::IntRect             textureRect;
    sf::Time                fireInterval;
    std::vector<Direction>  directions;
};

struct ProjectileData
{
    int                     damage;
    float                   speed;
    Textures::ID            texture;
};

struct PickupData
{
    std::function<void(Spaceship&)>
                            action;
    Textures::ID            texture;
};

std::vector<SpaceshipData>  initializeSpaceshipData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData>     initializePickupData();


#endif /* DataTables_hpp */
