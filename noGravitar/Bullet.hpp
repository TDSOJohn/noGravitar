//
//  Bullet.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
// Costruttore di copia t(const t& oggetto);

#ifndef Bullet_hpp
#define Bullet_hpp

#include "Core/ResourceHolder.hpp"
#include "Core/GameEntity.hpp"


class Bullet : public GameEntity
{
public:
    Bullet(const sf::Texture&, entitySettings = Settings::BULLET_3, sf::Vector2f = sf::Vector2f()); //int is damage, float is rotation angle
    
    bool                move(const sf::Time& = sf::Time());                                 //Return 0 if bullet no longer inside map coordinates
    int                 getDamage() { return settings.damage; }
    sf::FloatRect       getBounds() const { return entitySprite.getGlobalBounds(); }
    
private:
    sf::Vector2f        directionVector;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(entitySprite);
    }
};

#endif /* Bullet_hpp */
