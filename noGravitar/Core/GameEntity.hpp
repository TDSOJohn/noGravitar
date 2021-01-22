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


class GameEntity : public sf::Drawable, public sf::Transformable
{
public:
    GameEntity(const sf::Texture&, const entitySettings& = entitySettings(), const sf::Vector2f& =sf::Vector2f());
    sf::FloatRect getBounds() const { return entitySprite.getGlobalBounds(); }
    
protected:
    entitySettings settings;
    sf::Sprite entitySprite;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(entitySprite, states);
    }
};

#endif /* GameEntity_hpp */