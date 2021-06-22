//
//  Projectile.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 13/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "Projectile.hpp"
#include "DataTables.hpp"
#include "Core/Utility.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


namespace
{
    const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures):
    GameEntity(1),
    mType(type),
    mSprite(textures.get(Table[type].texture)),
    mTargetDirection()
{
    centerOrigin(mSprite);
}

void Projectile::guideTowards(sf::Vector2f position)
{
    assert(isGuided());
    mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
    return mType == Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (isGuided())
    {
        const float approachRate = 200.f;

        sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());
        newVelocity *= getMaxSpeed();
        float angle = std::atan2(newVelocity.y, newVelocity.x);

        setRotation(toDegree(angle) + 90.f);
        setVelocity(newVelocity);
    }

    GameEntity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
    if (mType == EnemyBullet)
        return Category::EnemyProjectile;
    else
        return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
    return Table[mType].speed;
}

int Projectile::getDamage() const
{
    return Table[mType].damage;
}
