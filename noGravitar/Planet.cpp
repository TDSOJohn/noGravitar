//
//  Planet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Planet.hpp"

Planet::Planet(const TextureHolder& textures, sf::Vector2f planetPosition) : planetSprite(textures.get(Textures::Planet)), planetBackground(textures.get(Textures::pBackground)), bulletTexture(textures.get(Textures::Bullet)), spaceshipBulletTime(sf::Time::Zero), enemyBulletTime(sf::Time::Zero), planetStatus(false)
{
    planetSprite.setOrigin(Settings::ICONS_DIM, Settings::ICONS_DIM);
    planetSprite.setPosition(planetPosition);
    
    ground.setPrimitiveType(sf::LineStrip);
    ground.resize(Settings::GROUND_POINTS);
    sf::Vector2f groundVector(0.f, Settings::MAP_Y/5*4);
    sf::Vector2f fuelVector(0.f, 0.f);
    for(int i=0; i<Settings::GROUND_POINTS; i++)
    {
        ground[i].position = groundVector;
        ground[i].color = sf::Color::Red;
        groundVector.x += Settings::MAP_X/(Settings::GROUND_POINTS-1);
        groundVector.y = rand()%240 + 960;
        if(i%2)                                     //Un fuel ogni 2 tratti di terreno
        {
            fuelVector = sf::Vector2f((ground[i-1].position.x + ground[i].position.x)/2, (ground[i-1].position.y + ground[i].position.y)/2);
            fuelArray.push_back(Fuel(textures.get(Textures::Fuel), fuelVector));
        } else if (i)                               //Un nemico ogni 2 tratti di terreno, non partendo da i=0 ma da i=2
        {
            fuelVector = sf::Vector2f((ground[i-1].position.x + ground[i].position.x)/2, (ground[i-1].position.y + ground[i].position.y)/2);
            enemyArray.push_back(Enemy(textures, fuelVector,
                                       std::atan((ground[i].position.y - ground[i-1].position.y)/
                                        (Settings::MAP_X/(Settings::GROUND_POINTS-1)))*180/PI)); //Pass angle of rotation of ground line
        }
    }
}

bool Planet::updatePlanet(Spaceship& spaceship, const sf::Time& deltaTime, sf::Vector2f& spaceshipMovement, bool isShooting, bool isGrabbing)
{
    bool collisions = checkCollisions(spaceship);
    
    if(!spaceship.getLife())
        return 0;
    
    if(!isGrabbing && !collisions)
        spaceship.move(spaceshipMovement * deltaTime.asSeconds(), isShooting, isGrabbing);
    if(!isGrabbing && collisions)
        spaceship.move(sf::Vector2f(0.f, -100.f) * deltaTime.asSeconds(), isShooting, isGrabbing);
    if(isGrabbing && !collisions)
        spaceship.move(sf::Vector2f(0.f, Settings::HOOK_SPEED) * deltaTime.asSeconds(), isShooting, isGrabbing);
    if(isGrabbing && collisions)
        spaceship.move(sf::Vector2f(0.f, 0.f), false, false);

    enemyBulletTime += deltaTime;
    spaceshipFuelConsumption += deltaTime;
    
    if(spaceshipFuelConsumption.asSeconds() >= 1)
    {
        spaceship.isHit(Settings::SPACESHIP_FUEL_RATE);
        spaceshipFuelConsumption -= sf::seconds(1.f);
    }
    if(spaceship.isShooting())                                            //Checks time for spaceship bullets
    {
        spaceshipBulletTime += deltaTime;
        if(spaceshipBulletTime.asSeconds() >= 1.f/Settings::SPACESHIP_FIRERATE)
        {
            spaceshipBulletArray.push_back(Bullet(bulletTexture, spaceship.getPosition(), Settings::SPACESHIP_DAMAGE, 180.f));
            spaceshipBulletTime -= sf::seconds(1.f/Settings::SPACESHIP_FIRERATE);
        }
    }
    
    if(enemyBulletTime.asSeconds() >= 1.f/Settings::ENEMY_FIRERATE)       //Checks time for enemy bullets, sometimes fires
    {
        for(int i=0; i<enemyArray.size(); i++)
            enemyBulletArray.push_back(Bullet(bulletTexture, enemyArray[i].getPosition(), Settings::ENEMY_DAMAGE, enemyArray[i].getRotation()));
        enemyBulletTime -= sf::seconds(1.f/Settings::ENEMY_FIRERATE);
    }
    
    for(int i=0; i < spaceshipBulletArray.size(); i++)                    //Update spaceship bullets' positions
    {
        if(!spaceshipBulletArray[i].move(deltaTime))
            spaceshipBulletArray.erase(spaceshipBulletArray.begin() + i); //Delete out_of_bounds bullets
    }
    for(int i=0; i < enemyBulletArray.size(); i++)                        //Update enemy bullets' positions
    {
        if(!enemyBulletArray[i].move(deltaTime))
            enemyBulletArray.erase(enemyBulletArray.begin() + i);         //Delete out_of_bounds bullets
    }
    
    if(enemyArray.size() == 0)                                            //If all enemy are destroyed, planet is complete
    {
        completed();
    }

    if(spaceship.isGrabbing())                                            //Check hook-fuel intersection
    {
        for(int i=0; i<fuelArray.size(); i++)
        {
            if(spaceship.getHookBounds().intersects(fuelArray[i].getBounds()))
            {
                spaceship.isHit(fuelArray[i].getFuel() * (-1));
                fuelArray.erase(fuelArray.begin() + i);
            }
        }
    }
    return 1;
}

void Planet::changeStatus(bool pStatus)
{
    planetStatus = pStatus;
    if(!planetStatus)
    {
        spaceshipBulletArray.clear();
        enemyBulletArray.clear();
    }
}

void Planet::fireBullet(const sf::Vector2f& spaceshipPosition)
{
    spaceshipBulletArray.push_back(Bullet(bulletTexture, spaceshipPosition, 180.f));
}

bool Planet::checkCollisions(Spaceship& spaceship)
{
    for(int i=0; i<enemyArray.size(); i++)                               //Check collisions between every enemy and every element of spaceshipBulletArray
    {
        for(int j=0; j<spaceshipBulletArray.size(); j++)
        {
            if(enemyArray[i] == spaceshipBulletArray[j])
            {
                if(!enemyArray[i].isHit(spaceshipBulletArray[i].getDamage()))
                    enemyArray.erase(enemyArray.begin() + i);
                spaceshipBulletArray.erase(spaceshipBulletArray.begin() + j);
            }
        }
    }
    for(int i=0; i<enemyBulletArray.size(); i++)                         //Check collisions between spaceship and avery enemyBulletArray
    {
        if(spaceship == enemyBulletArray[i])
        {
            if(!spaceship.isHit(enemyBulletArray[i].getDamage()))
                ;                                                //!!! - se la vita dell'astronave finisce
            enemyBulletArray.erase(enemyBulletArray.begin() + i);
        }
    }

    if(spaceship.getBounds().intersects(ground.getBounds()))
        return 1;
    return 0;
}

void Planet::completed()
{
    planetSprite.setColor(sf::Color::Red);
}
