//
//  Character.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Character.hpp"

Character::Character(const TextureHolder textures, sf::Vector2f position, float rotation) : lifeBar(sf::Vector2f(life, 4.f))
{
    characterSprite.setOrigin(Settings::ICONS_DIM/2, Settings::ICONS_DIM/2);
    characterSprite.setPosition(position);
    characterSprite.setRotation(rotation);
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setOrigin(life/2, 2.f);
    lifeBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}

Character::~Character()
{
    
}

int Character::isHit(int damage)
{
    life -= damage;
    if(life <0)
        life =0;
    lifeBar.setSize(sf::Vector2f(life, 4.f));

    return life;
}

bool Character::operator==(const Bullet& b)
{
    return(characterSprite.getGlobalBounds().intersects(b.getBounds()));
}
