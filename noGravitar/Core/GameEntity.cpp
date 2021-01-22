//
//  GameEntity.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/08/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "GameEntity.hpp"

GameEntity::GameEntity(const sf::Texture& texture, const entitySettings& eSettings, const sf::Vector2f& position) :
                settings(eSettings), entitySprite(texture)
{
    this->setOrigin(entitySprite.getLocalBounds().width/2, entitySprite.getLocalBounds().height/2);
    this->setPosition(position);
    this->setRotation(settings.rotation);
}
