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
        planetArray.push_back(planetCell { (Planet(textures, sf::Vector2f(Settings::MAP_X/(Settings::PLANETS+1)*(i+1), rand()%(Settings::MAP_Y - Settings::ICONS_DIM)+Settings::ICONS_DIM))), false });
    }
}

SolarSystem::~SolarSystem()
{
//    ourHero.~Spaceship();
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

int SolarSystem::update(sf::Time deltaTime)
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
        int temp = planetArray[solarSystemStatus].planet.updatePlanet(ourHero, deltaTime, movement, isShooting, isGrabbing);
        int temp2 = 0;
        if(temp == 2)
            planetArray[solarSystemStatus].status = true;
        else
            return temp;
        for(int i=0; i<Settings::PLANETS; i++)
            temp2 += planetArray[i].status;
        if(temp2 == Settings::PLANETS)
            return 2;
    }
    return 1;
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
