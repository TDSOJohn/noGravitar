//
//  GameEntity.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/08/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef GameEntity_hpp
#define GameEntity_hpp

#include "SceneNode.hpp"



class GameEntity : public SceneNode
{
public:
    explicit                    GameEntity(int hitpoints);
    
    void                        setVelocity(sf::Vector2f velocity);
    void                        setVelocity(float vx, float vy);

    void                        accelerate(sf::Vector2f velocity);
    void                        accelerate(float vx, float vy);
    
    sf::Vector2f                getVelocity() const;
    
    int                         getHitpoints() const;
    void                        repair(int points);
    void                        damage(int points);
    void                        destroy();
    bool                        isDestroyed() const;

    
    
protected:
    sf::Vector2f                mVelocity;
    int                         mHitpoints;

protected:
    virtual void                updateCurrent(sf::Time dt, CommandQueue& commands);
};

#endif /* GameEntity_hpp */
