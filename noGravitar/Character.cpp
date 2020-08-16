//
//  Character.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 15/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Character.hpp"

Character::Character(const TextureHolder& resources, Textures::ID textureID, sf::Vector2f position, float rotation) : characterSprite(resources.get(textureID))
{
    if(textureID == Textures::Enemy_1)
        settings = Settings::ENEMY_1;
    else
        settings = Settings::ENEMY_2;
    
    settings.rotation = rotation;
    characterSprite.setOrigin(characterSprite.getLocalBounds().width/2, characterSprite.getLocalBounds().height/2);
    characterSprite.setPosition(position);
    characterSprite.setRotation(settings.rotation);
    
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
    lifeBar.setPosition(characterSprite.getPosition() - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
    
    return settings.life;
}

bool Character::operator==(const Bullet& b)
{
    return(characterSprite.getGlobalBounds().intersects(b.getBounds()));
}
