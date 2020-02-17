//
//  Fuel.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 28/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Fuel.hpp"

Fuel::Fuel(const sf::Texture& fuelText, sf::Vector2f fuelPosition)
{
    fuelQuantity = rand()%40 + 10;
    fuelSprite.setOrigin(Settings::ICONS_DIM/2, Settings::ICONS_DIM/4);
    
    fuelSprite.setTexture(fuelText);
    fuelSprite.setPosition(fuelPosition);
    fuelSprite.setColor(sf::Color(255 -(fuelQuantity*5), (fuelQuantity*5), 0, 255));
}
