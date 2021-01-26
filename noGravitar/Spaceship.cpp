//
//  Spaceship.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"
#include "Core/Category.hpp"



Textures::ID toTextureID(Spaceship::Type type)
{
    switch (type)
    {
        case Spaceship::Old_Fart:
            return Textures::Eagle;
            
        case Spaceship::Flying_Hippo:
            return Textures::Raptor;
            
        default:
            return Textures::Eagle;
    }
}

Spaceship::Spaceship(Type type, const TextureHolder& textures) :
    mType(type),
    mSprite(textures.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void Spaceship::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


unsigned int Spaceship::getCategory() const
{
    switch (mType)
    {
        case Old_Fart:
            return Category::PlayerShip;
            
        default:
            return Category::EnemyShip;
    }
}
