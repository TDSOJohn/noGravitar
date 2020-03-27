//
//  GameEntity.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 19/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include <iostream>
#include "GameEntity.hpp"

GameEntity::GameEntity(const sf::Texture& texture, const entitySettings& eSettings,
                       const sf::Vector2f& position, float rotation) : entitySprite(texture), settings(eSettings)
{
    settings.rotation = rotation;
    this->setOrigin(entitySprite.getLocalBounds().width/2, entitySprite.getLocalBounds().height/2);
 //   std::cout <<this->getOrigin().x <<std::endl <<this->getOrigin().y <<std::endl;
    this->setPosition(position);
    this->setRotation(settings.rotation);
}
