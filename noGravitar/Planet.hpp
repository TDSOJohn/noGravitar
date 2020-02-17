//
//  Planet.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Planet_hpp
#define Planet_hpp

#include "ResourceHolder.hpp"
#include "Spaceship.hpp"
#include "Enemy.hpp"
#include "Fuel.hpp"
#include "Bullet.hpp"

class Planet : public sf::Drawable
{
public:
    Planet(int*, const ResourceHolder& =ResourceHolder(), sf::Vector2f =sf::Vector2f());
    
    void                changeStatus(bool pStatus);
    void                fireBullet(const sf::Vector2f&);

    sf::FloatRect       getBounds() { return planetSprite.getGlobalBounds(); }
    Settings::gameStates updatePlanet(Spaceship&, const sf::Time&, sf::Vector2f&, bool, bool);   //Return is 1 if spaceship alive, 0 is dead, 2 if planet complete
                                                                                                //Spaceship, Time since last update, isShooting, isGrabbing

private:
    sf::Sprite          planetSprite;
    sf::Sprite          planetBackground;
    sf::VertexArray     ground;
    const sf::Texture&  bulletTexture;
    sf::Time            spaceshipBulletTime;
    sf::Time            enemyBulletTime;
    sf::Time            spaceshipFuelConsumption;
    
    std::vector<Fuel>   fuelArray;
    std::vector<Enemy>  enemyArray;
    std::vector<Bullet> spaceshipBulletArray;
    std::vector<Bullet> enemyBulletArray;
    
    int*                score;
    bool                planetStatus;       //0 for Solar System view, 1 for Planet view
    
    bool                checkCollisions(Spaceship&);
    void                completed();
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(!planetStatus)
            target.draw(planetSprite);
        else
        {
            target.draw(planetBackground);
            target.draw(ground);
            
            for(int i= 0; i<fuelArray.size(); i++)
                target.draw(fuelArray[i]);
            for(int i= 0; i<enemyArray.size(); i++)
                target.draw(enemyArray[i]);
            for(int i=0; i<spaceshipBulletArray.size(); i++)
                target.draw(spaceshipBulletArray[i]);
            for(int i=0; i<enemyBulletArray.size(); i++)
                target.draw(enemyBulletArray[i]);
        }
    }
};

#endif /* Planet_hpp */
