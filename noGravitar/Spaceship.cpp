//
//  Spaceship.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"

Spaceship::Spaceship(const ResourceHolder& resources, Textures::ID textureID, sf::Vector2f position) : Character(resources, textureID, position, 0), hookSprite(resources.get(Textures::Hook)), grabbing(false)
{
    settings = Settings::SPACESHIP;
    characterSprite.setTexture(resources.get(textureID));
    characterSprite.setOrigin(characterSprite.getLocalBounds().width/2, characterSprite.getLocalBounds().height/2);
    lifeBar.setOrigin(settings.life/2, 3.f);
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    hookSprite.setOrigin(Settings::ICONS_DIM/4, Settings::ICONS_DIM/4);
    characterSprite.setPosition(position);
}

void Spaceship::move(sf::Vector2f movement, bool shotInput, bool grabInput) //moving the hook if grabInput =1
{
    shooting = shotInput;
    grabbing = grabInput;
    if(!grabbing)
    {
        characterSprite.move(movement);
        if(characterSprite.getPosition().x < Settings::ICONS_DIM/2)
            characterSprite.setPosition(Settings::ICONS_DIM/2, characterSprite.getPosition().y);
        else if(characterSprite.getPosition().x > (Settings::MAP_X - Settings::ICONS_DIM/2))
            characterSprite.setPosition((Settings::MAP_X - Settings::ICONS_DIM/2), characterSprite.getPosition().y);
        if(characterSprite.getPosition().y < Settings::ICONS_DIM/2)
            characterSprite.setPosition(characterSprite.getPosition().x, Settings::ICONS_DIM/2);
        else if(characterSprite.getPosition().y > (Settings::MAP_Y - Settings::ICONS_DIM/2))
            characterSprite.setPosition(characterSprite.getPosition().x, (Settings::MAP_Y - Settings::ICONS_DIM/2));

        lifeBar.setPosition(characterSprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
        hookSprite.setPosition(characterSprite.getPosition() + sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    }
    else
    {
        hookSprite.move(movement);
    }
}

void Spaceship::move(sf::Vector2f newPos)
{
    characterSprite.setPosition(newPos);
    lifeBar.setPosition(newPos - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}

/*
 
 if(spaceshipFuelConsumption.asSeconds() >= 1)
 {
 spaceship.isHit(1);
 spaceshipFuelConsumption -= sf::seconds(1.f);
 }
*/
