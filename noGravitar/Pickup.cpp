//
//  Pickup.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 13/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "Pickup.hpp"
#include "DataTables.hpp"
#include "Core/Category.hpp"
#include "Core/CommandQueue.hpp"
#include "Core/Utility.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


namespace
{
    const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures):
    GameEntity(1),
    mType(type),
    mSprite(textures.get(Table[type].texture))
{
    centerOrigin(mSprite);
}

unsigned int Pickup::getCategory() const
{
    return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::apply(Spaceship& player) const
{
    Table[mType].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

