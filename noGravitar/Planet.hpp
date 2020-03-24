//
//  Planet.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Planet_hpp
#define Planet_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "ResourceHolder.hpp"
#include "Spaceship.hpp"
#include "Enemy.hpp"
#include "Fuel.hpp"
#include "Bullet.hpp"

class Planet : public sf::Drawable
{
public:
    Planet(int*, const ResourceHolder<sf::Texture, Textures::ID>& =ResourceHolder<sf::Texture, Textures::ID>(), sf::Vector2f =sf::Vector2f());
    
    void                changeStatus(bool pStatus);

    sf::FloatRect       getBounds() { return planetSprite.getGlobalBounds(); }
    Settings::gameStates updatePlanet(Spaceship&, const sf::Time&, sf::Vector2f&, bool, bool);   //Return is ::Play if spaceship alive, ::Lost is dead, ::Won if planet
                                                                                                 //complete
                                                                                                 //Spaceship, Time since last update, isShooting, isGrabbing

private:
    sf::Sprite          planetSprite;
    sf::Sprite          planetBackground;
    sf::VertexArray     ground;
    const sf::Texture   bulletTexture;
    sf::Time            spaceshipBulletTime;
    sf::Time            enemyBullet1Time;
    sf::Time            enemyBullet2Time;
    
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
            
            for(auto i : fuelArray)
                target.draw(i);
            for(auto i : enemyArray)
                target.draw(i);
            for(auto i : spaceshipBulletArray)
                target.draw(i);
            for(auto i : enemyBulletArray)
                target.draw(i);
        }
    }
};

#endif /* Planet_hpp */
