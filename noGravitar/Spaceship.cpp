//
//  Spaceship.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"

Spaceship::Spaceship(const ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID textureID, sf::Vector2f position) : Character(textures.get(textureID), Settings::SPACESHIP, position, 0), fuelBar(sf::Vector2f(Settings::SPACESHIP_FUEL, 6.f)), hookSprite(textures.get(Textures::Hook)), fuel(Settings::SPACESHIP_FUEL), grabbing(false), clock(), fuelConsumption(sf::Time::Zero)
{
    settings = Settings::SPACESHIP;
    fuelBar.setOrigin(fuel/2, 3.f);
    fuelBar.setFillColor(sf::Color::Blue);
    fuelBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2 +12));
    hookSprite.setOrigin(Settings::ICONS_DIM/4, Settings::ICONS_DIM/4);
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
        entitySprite.move(movement);
        if(entitySprite.getPosition().x < Settings::ICONS_DIM/2)
            entitySprite.setPosition(Settings::ICONS_DIM/2, entitySprite.getPosition().y);
        else if(entitySprite.getPosition().x > (Settings::MAP_X - Settings::ICONS_DIM/2))
            entitySprite.setPosition((Settings::MAP_X - Settings::ICONS_DIM/2), entitySprite.getPosition().y);
        if(entitySprite.getPosition().y < Settings::ICONS_DIM/2)
            entitySprite.setPosition(entitySprite.getPosition().x, Settings::ICONS_DIM/2);
        else if(entitySprite.getPosition().y > (Settings::MAP_Y - Settings::ICONS_DIM/2))
            entitySprite.setPosition(entitySprite.getPosition().x, (Settings::MAP_Y - Settings::ICONS_DIM/2));

        lifeBar.setPosition(entitySprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
        fuelBar.setPosition(entitySprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2 +12));
        hookSprite.setPosition(entitySprite.getPosition() + sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    }
    else
    {
        hookSprite.move(movement);
    }
    if(fuel == 0)
        return Settings::gameStates::Lost;
    return Settings::gameStates::Play;
}
/*
void Spaceship::move(sf::Vector2f newPos)
{
    entitySprite.setPosition(newPos);
    lifeBar.setPosition(newPos - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}*/

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
