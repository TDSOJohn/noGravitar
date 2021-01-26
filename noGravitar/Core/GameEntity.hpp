//
//  GameEntity.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/08/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef GameEntity_hpp
#define GameEntity_hpp

#include <SFML/Graphics.hpp>


#include "Settings.h"
#include "ResourceHolder.hpp"

#include "SceneNode.hpp"



class GameEntity : public SceneNode
{
public:
    GameEntity(const entitySettings& = entitySettings());
    
    void                        setVelocity(const sf::Vector2f& v_in);
    void                        setVelocity(float v_in_x, float v_in_y);

    sf::Vector2f                getVelocity() const;
    
    
protected:
    entitySettings              settings;

    
private:
    virtual void                updateCurrent(sf::Time dt);
};

#endif /* GameEntity_hpp */
