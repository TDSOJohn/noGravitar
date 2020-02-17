//
//  SolarSystem.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef SolarSystem_hpp
#define SolarSystem_hpp

#include "ResourceHolder.hpp"
#include "Spaceship.hpp"
#include "Planet.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

struct planetCell
{
    Planet planet;
    bool status;                //1 for completed, 0 otherwise
};

class SolarSystem: public sf::Drawable
{
public:
    SolarSystem(int*, const ResourceHolder& = ResourceHolder());
    ~SolarSystem();
    void                handleInputEvent(sf::Keyboard::Key key, bool isMoving);
    Settings::gameStates update(sf::Time deltaTime);         //Returns 0 if spaceship dead, 1 if everything ok, 2 if planet complete
    sf::Vector2f        getSpaceshipPosition() { return(ourHero.getPosition()); }
    
private:
    bool                checkCollisions();
    
    sf::Sprite          ssBackgroundSprite;
    Spaceship           ourHero;
    std::vector<planetCell> planetArray;
    
    int*                score;
    bool                movingUp,
                        movingDown,
                        movingLeft,
                        movingRight,
                        isGrabbing,
                        isShooting;
    
    short               solarSystemStatus;                  //-1 for Solar System, i for planet[i]

    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(solarSystemStatus == -1)
        {
            target.draw(ssBackgroundSprite);
            for(int i=0; i<Settings::PLANETS; i++)
                target.draw(planetArray[i].planet);
        } else
            target.draw(planetArray[solarSystemStatus].planet);

        target.draw(ourHero);
    }
};

#endif /* SolarSystem_hpp */
