//
//  Planet.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 26/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Planet.hpp"

Planet::Planet(int* scr, const ResourceHolder& resources, sf::Vector2f planetPosition) : planetSprite(*(resources.get(Textures::Planet).texture)), planetBackground(*(resources.get(Textures::pBackground).texture)), bulletTexture(*(resources.get(Textures::Bullet).texture)), spaceshipBulletTime(sf::Time::Zero), enemyBulletTime(sf::Time::Zero), planetStatus(false), score(scr)
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
            fuelArray.push_back(Fuel(*(resources.get(Textures::Fuel).texture), fuelVector));
        } else if (i)                               //Un nemico ogni 2 tratti di terreno, non partendo da i=0 ma da i=2
        {
            fuelVector = sf::Vector2f((ground[i-1].position.x + ground[i].position.x)/2, (ground[i-1].position.y + ground[i].position.y)/2);
            enemyArray.push_back(Enemy(resources, Textures::Enemy_1, fuelVector,
                                       std::atan((ground[i].position.y - ground[i-1].position.y)/
                                        (Settings::MAP_X/(Settings::GROUND_POINTS-1)))*180/PI)); //Pass angle of rotation of ground line
        }
    }
}

Settings::gameStates Planet::updatePlanet(Spaceship& spaceship, const sf::Time& deltaTime, sf::Vector2f& spaceshipMovement, bool isShooting, bool isGrabbing)
{
    bool collisions = checkCollisions(spaceship);
    
    if(!spaceship.getLife())
        return Settings::gameStates::Lost;
    
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
        spaceship.isHit(1);
        spaceshipFuelConsumption -= sf::seconds(1.f);
    }
    if(spaceship.isShooting())                                            //Checks time for spaceship bullets
    {
        spaceshipBulletTime += deltaTime;
        if(spaceshipBulletTime.asSeconds() >= 1.f/Settings::SPACESHIP.FIRERATE)
        {
            spaceshipBulletArray.push_back(Bullet(bulletTexture, spaceship.getPosition(), Settings::SPACESHIP.DAMAGE, 180.f));
            spaceshipBulletTime -= sf::seconds(1.f/Settings::SPACESHIP.FIRERATE);
        }
    }
    
    if(enemyBulletTime.asSeconds() >= 1.f/Settings::ENEMY_1.FIRERATE)       //Checks time for enemy bullets, sometimes fires
    {
        for(int i=0; i<enemyArray.size(); i++)
            enemyBulletArray.push_back(Bullet(bulletTexture, enemyArray[i].getPosition(), Settings::ENEMY_1.DAMAGE, enemyArray[i].getRotation()));
        enemyBulletTime -= sf::seconds(1.f/Settings::ENEMY_1.FIRERATE);
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
        return Settings::gameStates::Won;
    }

    if(spaceship.isGrabbing())                                            //Check hook-fuel intersection
    {
        for(int i=0; i<fuelArray.size(); i++)
        {
            if(spaceship.getHookBounds().intersects(fuelArray[i].getBounds()))
            {
                spaceship.isHit(fuelArray[i].getFuel() * (-1));
                *score += fuelArray[i].getFuel();
                fuelArray.erase(fuelArray.begin() + i);
            }
        }
    }
    return Settings::gameStates::Play;
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
                {
                    *score += 100;
                    enemyArray.erase(enemyArray.begin() + i);
                }
                *score += 10;
                spaceshipBulletArray.erase(spaceshipBulletArray.begin() + j);
            }
        }
    }
    for(int i=0; i<enemyBulletArray.size(); i++)                         //Check collisions between spaceship and avery enemyBulletArray
    {
        if(spaceship == enemyBulletArray[i])
        {
            spaceship.isHit(enemyBulletArray[i].getDamage());
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
