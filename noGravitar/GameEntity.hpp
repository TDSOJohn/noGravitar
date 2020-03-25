//
//  GameEntity.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 19/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef GameEntity_hpp
#define GameEntity_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"


class GameEntity : public sf::Drawable, public sf::Transformable
{
public:
    GameEntity(const sf::Texture& =sf::Texture(), const entitySettings& =entitySettings(),
               const sf::Vector2f& =sf::Vector2f(), float =0.f);

    sf::FloatRect       getBounds() const { return entitySprite.getGlobalBounds(); }
    
protected:
    entitySettings      settings;
    sf::Sprite          entitySprite;

private:
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(entitySprite);
    }
};

#endif /* GameEntity_hpp */
