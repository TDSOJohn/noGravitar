//
//  Bullet.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 03/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
// Costruttore di copia t(const t& oggetto);

#ifndef Bullet_hpp
#define Bullet_hpp

#include "ResourceHolder.hpp"

class Bullet : public sf::Drawable
{
public:
    Bullet(const sf::Texture& = sf::Texture(), sf::Vector2f = sf::Vector2f(), int = 0, float = 0.f); //int is damage, float is rotation angle

    bool                move(const sf::Time& = sf::Time());                                 //Return 0 if bullet no longer inside map coordinates
    int                 getDamage() { return settings.damage; }
    sf::FloatRect       getBounds() const { return bulletSprite.getGlobalBounds(); }

private:
    entitySettings      settings;
    sf::Vector2f        directionVector;
    sf::Sprite          bulletSprite;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(bulletSprite);
    }
};

#endif /* Bullet_hpp */
