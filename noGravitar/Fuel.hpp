//
//  Fuel.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 28/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Fuel_hpp
#define Fuel_hpp

#include "ResourceHolder.hpp"

class Fuel : public sf::Drawable
{
public:
    Fuel(const sf::Texture& = sf::Texture(), sf::Vector2f = sf::Vector2f());
    ~Fuel();
    int                 getFuel()      { return fuelQuantity; }
    sf::FloatRect       getBounds()    { return fuelSprite.getGlobalBounds(); }
    
private:
    sf::Sprite          fuelSprite;
    int                 fuelQuantity;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(fuelSprite);
    }
};

#endif /* Fuel_hpp */
