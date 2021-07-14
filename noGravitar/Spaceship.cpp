//
//  Spaceship.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"
#include "DataTables.hpp"
#include "Core/Utility.hpp"
#include "Pickup.hpp"
#include "Core/CommandQueue.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace
{
    const std::vector<SpaceshipData> Table = initializeSpaceshipData();
}

Spaceship::Spaceship(Type type, const TextureHolder& textures, const FontHolder& fonts):
    GameEntity(Table[type].life),
    mType(type),
    mFireCommand(),
    mMissileCommand(),
    mFireCountdown(sf::Time::Zero),
    mIsFiring(false),
    mIsLaunchingMissile(false),
    mIsMarkedForRemoval(false),
    mSprite(textures.get(Table[type].texture), Table[type].textureRect),
    mFireRateLevel(1),
    mSpreadLevel(2),
    mMissileAmmo(2),
    mFuel(100),
    mDropPickupCommand(),
    mTravelledDistance(0.f),
    mDirectionIndex(0),
    mFuelDisplay(nullptr),
    mMissileDisplay(nullptr)
{
    centerOrigin(mSprite);

    mFireCommand.category   = Category::Scene;
    mFireCommand.action     = [this, &textures] (SceneNode& node, sf::Time)
    {
        createBullets(node, textures);
    };
    
    mMissileCommand.category= Category::Scene;
    mMissileCommand.action  = [this, &textures] (SceneNode& node, sf::Time)
    {
        createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
    };

    mDropPickupCommand.category = Category::Scene;
    mDropPickupCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
    {
        createPickup(node, textures);
    };

    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
    mHealthDisplay = healthDisplay.get();
    attachChild(std::move(healthDisplay));

    if (getCategory() == Category::PlayerShip)
    {
        std::unique_ptr<TextNode> fuelDisplay(new TextNode(fonts, ""));
        fuelDisplay->setPosition(0, 70);
        mFuelDisplay = fuelDisplay.get();
        attachChild(std::move(fuelDisplay));

        std::unique_ptr<TextNode> missileDisplay(new TextNode(fonts, ""));
        missileDisplay->setPosition(0, 100);
        mMissileDisplay = missileDisplay.get();
        attachChild(std::move(missileDisplay));
    }

    updateTexts();
}

void Spaceship::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Spaceship::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // Entity has been destroyed: Possibly drop pickup, mark for removal
    if (isDestroyed())
    {
        checkPickupDrop(commands);

        mIsMarkedForRemoval = true;
        return;
    }

    // Check if bullets or missiles are fired
    checkProjectileLaunch(dt, commands);

    // Update enemy movement pattern; apply velocity
    updateMovementPattern(dt);
    GameEntity::updateCurrent(dt, commands);

    // Update texts
    updateTexts();
}

unsigned int Spaceship::getCategory() const
{
    if (isAllied())
        return Category::PlayerShip;
    else
        return Category::EnemyShip;
}

sf::FloatRect Spaceship::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Spaceship::isMarkedForRemoval() const
{
    return mIsMarkedForRemoval;
}

bool Spaceship::isAllied() const
{
    return (mType == Old_Fart || mType == Flying_Hippo || mType == Speed_Junkie || mType == Psychedelic_Space_Teapot);
}

float Spaceship::getMaxSpeed() const
{
    return Table[mType].speed;
}

void Spaceship::increaseFireRate()
{
    if (mFireRateLevel < 10)
        ++mFireRateLevel;
}

void Spaceship::increaseSpread()
{
    if (mSpreadLevel < 3)
        ++mSpreadLevel;
}

void Spaceship::collectFuel(unsigned int count)
{
    mFuel += count;
}

void Spaceship::collectMissiles(unsigned int count)
{
    mMissileAmmo += count;
}

void Spaceship::fire()
{
    // Only ships with fire interval != 0 are able to fire
    if (Table[mType].fireInterval != sf::Time::Zero)
        mIsFiring = true;
}

void Spaceship::launchMissile()
{
    if(mMissileAmmo > 0)
    {
        mIsLaunchingMissile = true;
        --mMissileAmmo;
    }
}

void Spaceship::updateMovementPattern(sf::Time dt)
{
    // Enemy airplane: Movement pattern
    const std::vector<Direction>& directions = Table[mType].directions;
    if (!directions.empty())
    {
        // Moved long enough in current direction: Change direction
        if (mTravelledDistance > directions[mDirectionIndex].distance)
        {
            mDirectionIndex = (mDirectionIndex + 1) % directions.size();
            mTravelledDistance = 0.f;
        }

        // Compute velocity from direction
        float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
        float vx = getMaxSpeed() * std::cos(radians);
        float vy = getMaxSpeed() * std::sin(radians);

        setVelocity(vx, vy);

        mTravelledDistance += getMaxSpeed() * dt.asSeconds();
    }
}

void Spaceship::checkPickupDrop(CommandQueue& commands)
{
    if (!isAllied() && randomInt(3) == 0)
        commands.push(mDropPickupCommand);
}

void Spaceship::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
    // Enemies try to fire all the time
    if (!isAllied())
        fire();

    // Check for automatic gunfire, allow only in intervals
    if (mIsFiring && mFireCountdown <= sf::Time::Zero)
    {
        // Interval expired: We can fire a new bullet
        commands.push(mFireCommand);
        mFireCountdown += Table[mType].fireInterval / (mFireRateLevel + 1.f);
        mIsFiring = false;
    }
    else if (mFireCountdown > sf::Time::Zero)
    {
        // Interval not expired: Decrease it further
        mFireCountdown -= dt;
        mIsFiring = false;
    }

    // Check for missile launch
    if (mIsLaunchingMissile)
    {
        commands.push(mMissileCommand);
        mIsLaunchingMissile = false;
    }
}

void Spaceship::createBullets(SceneNode& node, const TextureHolder& textures) const
{
    Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

    switch (mSpreadLevel)
    {
        case 1:
            createProjectile(node, type, 0.0f, 0.5f, textures);
            break;

        case 2:
            createProjectile(node, type, -0.33f, 0.33f, textures);
            createProjectile(node, type, +0.33f, 0.33f, textures);
            break;

        case 3:
            createProjectile(node, type, -0.5f, 0.33f, textures);
            createProjectile(node, type,  0.0f, 0.5f, textures);
            createProjectile(node, type, +0.5f, 0.33f, textures);
            break;
    }
}

void Spaceship::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

    sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
    sf::Vector2f velocity(0, projectile->getMaxSpeed());

    float sign = isAllied() ? -1.f : +1.f;
    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);
    node.attachChild(std::move(projectile));
}

void Spaceship::createPickup(SceneNode& node, const TextureHolder& textures) const
{
    auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

    std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
    pickup->setPosition(getWorldPosition());
    pickup->setVelocity(0.f, 1.f);
    node.attachChild(std::move(pickup));
}

void Spaceship::updateTexts()
{
    mHealthDisplay->setString(toString(getHitpoints()) + " HP");
    mHealthDisplay->setPosition(0.f, 50.f);
    mHealthDisplay->setRotation(-getRotation());
    
    if(mMissileDisplay)
    {
        if (mMissileAmmo == 0)
            mMissileDisplay->setString("");
        else
            mMissileDisplay->setString("M: " + toString(mMissileAmmo));
    }
    
    if(mFuelDisplay)
    {
        mFuelDisplay->setString("F: " + toString(mFuel));
    }
}
