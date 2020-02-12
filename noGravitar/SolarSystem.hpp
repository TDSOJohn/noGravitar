//
//  SolarSystem.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef SolarSystem_hpp
#define SolarSystem_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "Spaceship.hpp"
#include "Planet.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class SolarSystem: public sf::Drawable
{
public:
    SolarSystem(const TextureHolder& = TextureHolder());
    ~SolarSystem();
    void                handleInputEvent(sf::Keyboard::Key key, bool isMoving);
    bool                update(sf::Time deltaTime);
    sf::Vector2f        getSpaceshipPosition() { return(ourHero.getPosition()); }
    
private:
    bool                checkCollisions();
    
    sf::Sprite          ssBackgroundSprite;
    Spaceship           ourHero;
    std::vector<Planet> planetArray;
    
    bool                movingUp,
                        movingDown,
                        movingLeft,
                        movingRight,
                        isGrabbing,
                        isShooting;
    
    short               solarSystemStatus;              //-1 for Solar System, i for planet[i]

    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(solarSystemStatus == -1)
        {
            target.draw(ssBackgroundSprite);
            for(int i=0; i<Settings::PLANETS; i++)
                target.draw(planetArray[i]);
        } else
            target.draw(planetArray[solarSystemStatus]);

        target.draw(ourHero);
    }
};

#endif /* SolarSystem_hpp */
