//
//  Enemy.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 04/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Enemy.hpp"
/*
Enemy::Enemy(const TextureHolder& textures, sf::Vector2f position, float rot) : enemySprite(textures.get(Textures::Enemy)), life(Settings::ENEMY_LIFE), lifeBar(sf::Vector2f(life, 4.f)), rotation(rot)
{
    enemySprite.setOrigin(Settings::ICONS_DIM/2, Settings::ICONS_DIM/2);
    enemySprite.setRotation(rotation);
    enemySprite.setPosition(position);
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setOrigin(Settings::ENEMY_LIFE/2, 2.f);
    lifeBar.setPosition(position - sf::Vector2f(0.f, Settings::ICONS_DIM/2));
}

Enemy::~Enemy()
{
    
}

int Enemy::isHit(int damage)
{
    life -= damage;
    if(life <0)
        life =0;
    lifeBar.setSize(sf::Vector2f(life, 4.f));
    
    return life;
}

bool Enemy::operator==(const Bullet& b)
{        
    return(enemySprite.getGlobalBounds().intersects(b.getBounds()));
}
*/
