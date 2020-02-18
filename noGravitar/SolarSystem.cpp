//
//  SolarSystem.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem(int* scr, const ResourceHolder& resources) : ourHero(resources, Textures::Spaceship), ssBackgroundSprite(resources.get(Textures::ssBackground)), solarSystemStatus(-1), movingUp(false), movingDown(false), movingLeft(false), movingRight(false), isGrabbing(false), isShooting(false), score(scr)
{
    int tempY =0;
    int i =0;
    
    while(planetArray.size()<Settings::PLANETS)
    {
        tempY = rand()%(Settings::MAP_Y - Settings::ICONS_DIM*2) + Settings::ICONS_DIM;
        if((tempY < (Settings::MAP_Y/3 - Settings::ICONS_DIM*2)) || (tempY > (Settings::MAP_Y/3 + Settings::ICONS_DIM*2)))
        {
            i++;
            planetArray.push_back(planetCell { (Planet(score, resources, sf::Vector2f(Settings::MAP_X/(Settings::PLANETS+1)*i, tempY))), false });
        }
    }
}

void SolarSystem::handleInputEvent(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::W:
            movingUp = isPressed;
            break;
        case sf::Keyboard::S:
            movingDown = isPressed;
            break;
        case sf::Keyboard::A:
            movingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            movingRight = isPressed;
            break;
        case sf::Keyboard::Space:
            if(solarSystemStatus != -1)
                isGrabbing = isPressed;
            else
                isGrabbing = false;
            break;
        case sf::Keyboard::K:
            if(solarSystemStatus != -1)
                isShooting = isPressed;
            else
                isShooting = false;
            break;
        case sf::Keyboard::Escape:
            planetArray[solarSystemStatus].planet.changeStatus(false);
            solarSystemStatus = -1;
            ourHero.move(sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
            break;

        default:
            break;
    }
}

Settings::gameStates SolarSystem::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (movingUp)
        movement.y -= Settings::SPACESHIP.speed;
    if (movingDown)
        movement.y += Settings::SPACESHIP.speed;
    if (movingLeft)
        movement.x -= Settings::SPACESHIP.speed;
    if (movingRight)
        movement.x += Settings::SPACESHIP.speed;
    
    if(solarSystemStatus == -1)             //If in solarSystem View, move spaceship and check collisions with planets
    {
        ourHero.move(movement * deltaTime.asSeconds(), false, false);
        checkCollisions();
    } else {
        Settings::gameStates temp = planetArray[solarSystemStatus].planet.updatePlanet(ourHero, deltaTime, movement, isShooting, isGrabbing);
        int temp2 = 0;
        if(temp == Settings::gameStates::Won)
        {
            planetArray[solarSystemStatus].status = true;
            for(int i=0; i<Settings::PLANETS; i++)
                temp2 += planetArray[i].status;
            if(temp2 == Settings::PLANETS)
                return Settings::gameStates::Won;
        } else
            return temp;
    }
    return Settings::gameStates::Play;
}

bool SolarSystem::checkCollisions()
{
    bool hit;
    sf::FloatRect ourHeroBounds = ourHero.getBounds();
    for(int i=0; i<planetArray.size(); i++)
    {
        hit = ourHeroBounds.intersects(planetArray[i].planet.getBounds());
        if(hit)
        {
            ourHero.move(sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
            planetArray[i].planet.changeStatus(hit);
            solarSystemStatus = i;
        }
    }
    return hit;
}
