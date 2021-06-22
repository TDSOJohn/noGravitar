//
//  Pickup.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 13/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Pickup_hpp
#define Pickup_hpp

#include "Core/GameEntity.hpp"
#include "Core/Command.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Spaceship;

class Pickup : public GameEntity
{
    public:
        enum Type
        {
            HealthRefill,
            MissileRefill,
            FireSpread,
            FireRate,
            TypeCount
        };


    public:
                                Pickup(Type type, const TextureHolder& textures);

        virtual unsigned int    getCategory() const;
        virtual sf::FloatRect   getBoundingRect() const;

        void                    apply(Spaceship& player) const;


    protected:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Type                    mType;
        sf::Sprite              mSprite;
};

#endif /* Pickup_hpp */
