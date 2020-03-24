//
//  Character.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Character.hpp"

Character::Character(const sf::Texture& texture, const entitySettings& settings, const sf::Vector2f& position, float rotation) : GameEntity(texture, settings, position, rotation)
{
    lifeBar.setSize(sf::Vector2f(settings.life, 4.f));
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setOrigin(settings.life/2, 2.f);
    lifeBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}

int Character::isHit(int damage)
{
    settings.life -= damage;
    if(settings.life <0)
        settings.life =0;
    lifeBar.setSize(sf::Vector2f(settings.life, 4.f));
    lifeBar.setOrigin(sf::Vector2f(settings.life/2, 2.f));
    lifeBar.setPosition(entitySprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));

    return settings.life;
}

bool Character::operator==(const Bullet& b)
{
    return(entitySprite.getGlobalBounds().intersects(b.getBounds()));
}
