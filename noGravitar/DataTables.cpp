//
//  DataTables.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 10/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "DataTables.hpp"

#include "DataTables.hpp"
#include "Spaceship.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<SpaceshipData> initializeSpaceshipData()
{
    std::vector<SpaceshipData> data(Spaceship::Typecount);

    data[Spaceship::Old_Fart].life = 100;
    data[Spaceship::Old_Fart].speed = 600.f;
    data[Spaceship::Old_Fart].fireInterval = sf::seconds(0.7f);
    data[Spaceship::Old_Fart].texture = Textures::Eagle;
    data[Spaceship::Old_Fart].textureRect = sf::IntRect(0, 0, 64, 119);

    data[Spaceship::Flying_Hippo].life = 150;
    data[Spaceship::Flying_Hippo].speed = 350.f;
    data[Spaceship::Flying_Hippo].fireInterval = sf::seconds(1);
    data[Spaceship::Flying_Hippo].texture = Textures::Eagle;
    data[Spaceship::Flying_Hippo].textureRect = sf::IntRect(0, 0, 64, 119);

    data[Spaceship::Speed_Junkie].life = 70;
    data[Spaceship::Speed_Junkie].speed = 700.f;
    data[Spaceship::Speed_Junkie].fireInterval = sf::seconds(1);
    data[Spaceship::Speed_Junkie].texture = Textures::Eagle;
    data[Spaceship::Speed_Junkie].textureRect = sf::IntRect(0, 0, 64, 119);

    data[Spaceship::Psychedelic_Space_Teapot].life = 130;
    data[Spaceship::Psychedelic_Space_Teapot].speed = 400.f;
    data[Spaceship::Psychedelic_Space_Teapot].fireInterval = sf::seconds(1);
    data[Spaceship::Psychedelic_Space_Teapot].texture = Textures::Eagle;
    data[Spaceship::Psychedelic_Space_Teapot].textureRect = sf::IntRect(0, 0, 64, 119);

    data[Spaceship::Enemy_1].life = 60;
    data[Spaceship::Enemy_1].speed = 300.f;
    data[Spaceship::Enemy_1].fireInterval = sf::seconds(1.3f);
    data[Spaceship::Enemy_1].texture = Textures::Enemy_1;
    data[Spaceship::Enemy_1].textureRect = sf::IntRect(0, 0, 65, 64);

    data[Spaceship::Enemy_1].directions.push_back(Direction(180.f, 300.f));
    data[Spaceship::Enemy_1].directions.push_back(Direction(270.f, 300.f));
    data[Spaceship::Enemy_1].directions.push_back(Direction(0.f, 300.f));
    data[Spaceship::Enemy_1].directions.push_back(Direction(90.f, 300.f));
    data[Spaceship::Enemy_1].textureRect = sf::IntRect(0, 0, 65, 64);

    data[Spaceship::Enemy_2].life = 40;
    data[Spaceship::Enemy_2].speed = 500.f;
    data[Spaceship::Enemy_2].fireInterval = sf::seconds(2.f);
    data[Spaceship::Enemy_2].texture = Textures::Enemy_2;
    data[Spaceship::Enemy_2].directions.push_back(Direction(240.f, 300.f));
    data[Spaceship::Enemy_2].directions.push_back(Direction(120.f, 300.f));
    data[Spaceship::Enemy_2].directions.push_back(Direction(0.f, 300.f));
    data[Spaceship::Enemy_2].textureRect = sf::IntRect(0, 0, 65, 64);

    return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::AlliedBullet].damage = 10;
    data[Projectile::AlliedBullet].speed = 600.f;
    data[Projectile::AlliedBullet].texture = Textures::Bullet_1;

    data[Projectile::EnemyBullet].damage = 10;
    data[Projectile::EnemyBullet].speed = 500.f;
    data[Projectile::EnemyBullet].texture = Textures::Bullet_2;

    data[Projectile::Missile].damage = 200;
    data[Projectile::Missile].speed = 150.f;
    data[Projectile::Missile].texture = Textures::Bullet_3;

    return data;
}

std::vector<PickupData> initializePickupData()
{
    std::vector<PickupData> data(Pickup::TypeCount);
    
    data[Pickup::HealthRefill].texture = Textures::Fuel;
    data[Pickup::HealthRefill].action = std::bind(&Spaceship::repair, _1, 25);
    
    data[Pickup::MissileRefill].texture = Textures::Fuel;
    data[Pickup::MissileRefill].action = std::bind(&Spaceship::collectMissiles, _1, 3);
  
    data[Pickup::FireSpread].texture = Textures::Hook;
    data[Pickup::FireSpread].action = std::bind(&Spaceship::increaseSpread, _1);

    data[Pickup::FireRate].texture = Textures::Hook;
    data[Pickup::FireRate].action = std::bind(&Spaceship::increaseFireRate, _1);

    return data;
}
