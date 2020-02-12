//
//  SolarSystem.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem(const TextureHolder& textures) : ourHero(textures), ssBackgroundSprite(textures.get(Textures::ssBackground)), solarSystemStatus(-1), movingUp(false), movingDown(false), movingLeft(false), movingRight(false), isGrabbing(false), isShooting(false)
{
    for(int i=0; i<Settings::PLANETS; i++)
    {
        planetArray.push_back(Planet(textures, sf::Vector2f(Settings::MAP_X/(Settings::PLANETS+1)*(i+1), rand()%(Settings::MAP_Y - Settings::ICONS_DIM)+Settings::ICONS_DIM)));
    }
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::handleInputEvent(sf::Keyboard::Key key, bool isPressed)
{
    switch (key) {
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
            planetArray[solarSystemStatus].changeStatus(false);
            solarSystemStatus = -1;
            ourHero.move(sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
            break;

        default:
            break;
    }
}

bool SolarSystem::update(sf::Time deltaTime)            //1 if still alive, 0 if ourHero is DE4D
{
    sf::Vector2f movement(0.f, 0.f);
    if (movingUp)
        movement.y -= Settings::SPACESHIP_SPEED;
    if (movingDown)
        movement.y += Settings::SPACESHIP_SPEED;
    if (movingLeft)
        movement.x -= Settings::SPACESHIP_SPEED;
    if (movingRight)
        movement.x += Settings::SPACESHIP_SPEED;
    
    if(solarSystemStatus == -1)
    {
        ourHero.move(movement * deltaTime.asSeconds(), false, false);
        checkCollisions();
    } else {
        if(!planetArray[solarSystemStatus].updatePlanet(ourHero, deltaTime, movement, isShooting, isGrabbing))
        {
            ourHero.~Spaceship();           //ourHero is dead! Long live ourHero!
            return 0;
        }
    }
    return 1;
}

bool SolarSystem::checkCollisions()
{
    bool hit;
    sf::FloatRect ourHeroBounds = ourHero.getBounds();
    for(int i=0; i<planetArray.size(); i++)
    {
        hit = ourHeroBounds.intersects(planetArray[i].getBounds());
        if(hit)
        {
            ourHero.move(sf::Vector2f(Settings::MAP_X/2, Settings::MAP_Y/3));
            planetArray[i].changeStatus(hit);
            solarSystemStatus = i;
        }
    }
    return hit;
}
