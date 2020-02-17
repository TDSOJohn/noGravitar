//
//  Spaceship.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 25/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Spaceship.hpp"

Spaceship::Spaceship(const ResourceHolder& resources, sf::Vector2f position) : spaceshipSprite(resources.get(Textures::Spaceship)), hookSprite(resources.get(Textures::Hook)), life(Settings::SPACESHIP.LIFE), lifeBar(sf::Vector2f(Settings::SPACESHIP.LIFE, 6.f)), shooting(false), grabbing(false)
{
    spaceshipSprite.setOrigin(Settings::ICONS_DIM/2, Settings::ICONS_DIM/2);
    lifeBar.setOrigin(life/2, 3.f);
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    hookSprite.setOrigin(Settings::ICONS_DIM/4, Settings::ICONS_DIM/4);
    spaceshipSprite.setPosition(position);
}

void Spaceship::move(sf::Vector2f movement, bool shotInput, bool grabInput) //moving the hook if grabInput =1
{
    shooting = shotInput;
    grabbing = grabInput;
    if(!grabbing)
    {
        spaceshipSprite.move(movement);
        if(spaceshipSprite.getPosition().x < Settings::ICONS_DIM/2)
            spaceshipSprite.setPosition(Settings::ICONS_DIM/2, spaceshipSprite.getPosition().y);
        else if(spaceshipSprite.getPosition().x > (Settings::MAP_X - Settings::ICONS_DIM/2))
            spaceshipSprite.setPosition((Settings::MAP_X - Settings::ICONS_DIM/2), spaceshipSprite.getPosition().y);
        if(spaceshipSprite.getPosition().y < Settings::ICONS_DIM/2)
            spaceshipSprite.setPosition(spaceshipSprite.getPosition().x, Settings::ICONS_DIM/2);
        else if(spaceshipSprite.getPosition().y > (Settings::MAP_Y - Settings::ICONS_DIM/2))
            spaceshipSprite.setPosition(spaceshipSprite.getPosition().x, (Settings::MAP_Y - Settings::ICONS_DIM/2));

        lifeBar.setPosition(spaceshipSprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
        hookSprite.setPosition(spaceshipSprite.getPosition() + sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    }
    else
    {
        hookSprite.move(movement);
    }
}

void Spaceship::move(sf::Vector2f newPos)
{
    spaceshipSprite.setPosition(newPos);
    lifeBar.setPosition(newPos - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}

bool Spaceship::operator==(const Bullet& b)
{
    return (spaceshipSprite.getGlobalBounds().intersects(b.getBounds()));
}

int Spaceship::isHit(int damage)
{
    life -= damage;
    lifeBar.setPosition(spaceshipSprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));

    if(life < 0)
        life =0;
    else if(life > 100)
        life =100;
    
    lifeBar.setSize(sf::Vector2f(life, 6.f));
    lifeBar.setOrigin(life/2, 3.f);

    return life;
}
