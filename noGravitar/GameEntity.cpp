//
//  GameEntity.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 19/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "GameEntity.hpp"

GameEntity::GameEntity(const entityResources& resources, sf::Vector2f position, float rotation) : entitySprite(*(resources.texture)), settings(resources.entityData)
{
    settings.rotation = rotation;
    entitySprite.setOrigin(entitySprite.getLocalBounds().width/2, entitySprite.getLocalBounds().height/2);
    entitySprite.setPosition(position);
    entitySprite.setRotation(settings.rotation);
}
