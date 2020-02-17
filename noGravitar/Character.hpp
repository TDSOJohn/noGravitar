//
//  Character.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include "ResourceHolder.hpp"

#include "Bullet.hpp"

class Character : public sf::Drawable
{
public:
    Character(const ResourceHolder& =ResourceHolder(), Textures::ID =Textures::Enemy_1, sf::Vector2f =sf::Vector2f(), float =0.f);
    
    bool                operator==(const Bullet&);
    int                 isHit(int);
 
    sf::Vector2f        getPosition()   { return characterSprite.getPosition(); }
    sf::FloatRect       getBounds()     { return characterSprite.getGlobalBounds(); }
    float               getRotation()   { return characterSprite.getRotation(); }
    int                 getLife()       { return life; }
    bool                isShooting()    { return shooting; }
    
protected:
    bool                shooting;
    int                 life;
    
    sf::Sprite          characterSprite;
    sf::RectangleShape  lifeBar;

private:
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(characterSprite);
        target.draw(lifeBar);
    }
};

#endif /* Character_hpp */
