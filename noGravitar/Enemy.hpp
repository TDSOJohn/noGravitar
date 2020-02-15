//
//  Enemy.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 04/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Settings.h"
#include "Bullet.hpp"

class Enemy : public sf::Drawable
{
    
    
public:
    Enemy(const TextureHolder& = TextureHolder(), sf::Vector2f = sf::Vector2f(), float =0);
    ~Enemy();

    bool                operator==(const Bullet&);                  //Operator == checks if enemy is hitting the bullet
    int                 isHit(int);                                 //Argument is damage. Returns updated life. If 0, enemy is dead
    sf::Vector2f        getPosition() { return enemySprite.getPosition(); }
    float               getRotation() { return rotation; }          //Returns rotation as angle in degrees float value

private:
    int                 life;
    float               rotation;
    
    sf::Sprite          enemySprite;
    sf::RectangleShape  lifeBar;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(enemySprite);
        target.draw(lifeBar);
    }
};

#endif /* Enemy_hpp */
