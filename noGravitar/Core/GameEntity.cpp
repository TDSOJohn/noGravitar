//
//  GameEntity.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/08/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "GameEntity.hpp"



GameEntity::GameEntity(const entitySettings& eSettings) :
                settings(eSettings)
{

}


void GameEntity::setVelocity(const sf::Vector2f& v_in)
{
    settings.velocity = v_in;
}


void GameEntity::setVelocity(float v_in_x, float v_in_y)
{
    settings.velocity.x = v_in_x;
    settings.velocity.y = v_in_y;
}


sf::Vector2f GameEntity::getVelocity() const
{
    return settings.velocity;
}


void GameEntity::updateCurrent(sf::Time dt)
{
    move(settings.velocity * dt.asSeconds());
}
