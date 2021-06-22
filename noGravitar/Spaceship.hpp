//
//  Spaceship.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp


#include "Core/GameEntity.hpp"
#include "Core/Command.hpp"
#include "Core/TextNode.hpp"
#include "ResourceIdentifiers.hpp"
#include "Projectile.hpp"

#include <SFML/Graphics/Sprite.hpp>


class CommandQueue;

class Spaceship : public GameEntity
{
public:
    enum Type
    {
        Old_Fart,
        Flying_Hippo,
        Speed_Junkie,
        Psychedelic_Space_Teapot,
        Enemy_1,
        Enemy_2,
        Typecount
    };
    
    Spaceship(Type type, const TextureHolder& textures, const FontHolder& fonts);
    
    void                            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void                    updateCurrent(sf::Time dt, CommandQueue& commands);
    unsigned int                    getCategory() const;
    virtual sf::FloatRect           getBoundingRect() const;
    virtual bool                    isMarkedForRemoval() const;
    bool                            isAllied() const;
    float                           getMaxSpeed() const;

    void                            increaseFireRate();
    void                            increaseSpread();
    void                            collectFuel(unsigned int count);
    void                            collectMissiles(unsigned int count);

    void                            fire();
    void                            launchMissile();

private:
    Type                            mType;
    sf::Sprite                      mSprite;
    Command                         mFireCommand;
    Command                         mMissileCommand;
    sf::Time                        mFireCountdown;
    bool                            mIsFiring;
    bool                            mIsLaunchingMissile;
    bool                            mIsMarkedForRemoval;

    int                             mFireRateLevel;
    int                             mSpreadLevel;
    int                             mFuel;
    int                             mMissileAmmo;

    Command                         mDropPickupCommand;
    float                           mTravelledDistance;
    std::size_t                     mDirectionIndex;
    TextNode*                       mHealthDisplay;
    TextNode*                       mFuelDisplay;
    TextNode*                       mMissileDisplay;

private:
    void                            updateMovementPattern(sf::Time dt);
    void                            checkPickupDrop(CommandQueue& commands);
    void                            checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

    void                            createBullets(SceneNode& node, const TextureHolder& textures) const;
    void                            createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
    void                            createPickup(SceneNode& node, const TextureHolder& textures) const;

    void                            updateTexts();

};

#endif /* Spaceship_hpp */
