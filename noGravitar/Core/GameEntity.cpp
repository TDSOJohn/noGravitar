//
//  GameEntity.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/08/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "GameEntity.hpp"

#include <cassert>



GameEntity::GameEntity(int hitpoints):
    mVelocity(),
    mHitpoints(hitpoints)
{}

void GameEntity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void GameEntity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void GameEntity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void GameEntity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

sf::Vector2f GameEntity::getVelocity() const
{
    return mVelocity;
}

int GameEntity::getHitpoints() const
{
    return mHitpoints;
}

void GameEntity::repair(int points)
{
    assert(points > 0);

    mHitpoints += points;
}

void GameEntity::damage(int points)
{
    assert(points > 0);
    
    mHitpoints -= points;
}

void GameEntity::destroy()
{
    mHitpoints = 0;
}

bool GameEntity::isDestroyed() const
{
    return(mHitpoints <= 0);
}

void GameEntity::updateCurrent(sf::Time dt, CommandQueue&)
{
    move(mVelocity * dt.asSeconds());
}
