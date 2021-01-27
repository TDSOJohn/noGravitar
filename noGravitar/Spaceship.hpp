//
//  Spaceship.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp


#include "Core/ResourceHolder.hpp"
#include "Core/GameEntity.hpp"



class Spaceship : public GameEntity
{
public:
    
    enum Type
    {
        Old_Fart,
        Flying_Hippo,
        Speed_Junkie,
        Psychedelic_Space_Teapot
    };
    
    
    Spaceship(Type type, const TextureHolder& textures);
    
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
    unsigned int                    getCategory() const;
   
    
private:
    Type                            mType;
    sf::Sprite                      mSprite;
    
};

#endif /* Spaceship_hpp */
