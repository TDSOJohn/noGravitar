//
//  Spaceship.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"

Spaceship::Spaceship(const ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID textureID, sf::Vector2f position) : Character(textures.get(textureID), Settings::SPACESHIP, sf::Vector2f(0.f, 0.f), 0), fuelBar(sf::Vector2f(Settings::SPACESHIP_FUEL, 6.f)), hook(textures.get(Textures::Hook)), fuel(Settings::SPACESHIP_FUEL), grabbing(false), clock(), fuelConsumption(sf::Time::Zero)
{
    this->setPosition(position);
    settings = Settings::SPACESHIP;
    fuelBar.setOrigin(fuel/2, 3.f);
    fuelBar.setFillColor(sf::Color::Blue);
    fuelBar.setPosition(this->getOrigin().x, -(Settings::ICONS_DIM/2 +12));
    hook.setPosition(this->getOrigin().x, Settings::ICONS_DIM/2);
}

Settings::gameStates Spaceship::move(sf::Vector2f movement, bool shotInput, bool grabInput) //moving the hook if grabInput =1
{
    fuelConsumption += clock.restart();
    if(fuelConsumption.asSeconds() >= 1)
    {
        fuelConsumption -= sf::seconds(1.f);
        if(fuel)
            fuel--;
        fuelBar.setSize(sf::Vector2f(fuel, 6.f));
        fuelBar.setOrigin(fuel/2, 3.f);

    }
    shooting = shotInput;
    grabbing = grabInput;
    if(!grabbing)
    {
        sf::Vector2f currPos =this->getPosition();
        sf::FloatRect bounds =this->getBounds();
        this->move(movement);
        if(currPos.x < Settings::ICONS_DIM/2)
            this->setPosition(Settings::ICONS_DIM/2, currPos.y);
        else if(currPos.x > (Settings::MAP_X - bounds.width/2))
            this->setPosition((Settings::MAP_X - bounds.width/2), currPos.y);
        if(currPos.y < bounds.height/2)
            this->setPosition(currPos.x, bounds.height/2);
        else if(currPos.y > (Settings::MAP_Y - bounds.height/2))
            this->setPosition(currPos.x, (Settings::MAP_Y - bounds.height/2));
        
        hook.setPosition(this->getOrigin().x, Settings::ICONS_DIM/2);
    }
    else
    {
        hook.move(movement);
    }
    if(fuel == 0)
        return Settings::gameStates::Lost;
    return Settings::gameStates::Play;
}

void Spaceship::addFuel(int f)
{
    fuel += f;
    if(fuel > Settings::SPACESHIP_FUEL*2)
        fuel = Settings::SPACESHIP_FUEL*2;
    fuelBar.setSize(sf::Vector2f(fuel, 6.f));
    fuelBar.setOrigin(fuel/2, 3.f);
}

int Spaceship::isHit(int damage)
{
    Character::isHit(damage);
    if(settings.life > Settings::SPACESHIP.life)
        settings.life = Settings::SPACESHIP.life;
    
    return settings.life;
}

/*
 
 if(spaceshipFuelConsumption.asSeconds() >= 1)
 {
 spaceship.isHit(1);
 spaceshipFuelConsumption -= sf::seconds(1.f);
 }
*/
