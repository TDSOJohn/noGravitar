//
//  World.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "World.hpp"

#include "Core/ResourcePath.hpp"



World::World()
{
    createTextures();
    
    this->gameOverlay = overlayPtr(new Overlay(textures, &gameState, &score));

}

void World::update(sf::Time dt)
{
    
}

void World::draw()
{
    
}

void World::createTextures()
{
    mTextures.load(Textures::Won,            resourcePath() + "youWon.png");
    mTextures.load(Textures::Lost,           resourcePath() + "youLost.png");
    
    mTextures.load(Textures::ssBackground,   resourcePath() + "ssBackground.png");
    mTextures.load(Textures::pBackground,    resourcePath() + "pBackground.png");
    mTextures.load(Textures::Planet,         resourcePath() + "planet.png");
    mTextures.load(Textures::Eagle,          resourcePath() + "spaceship.png");
    mTextures.load(Textures::Raptor,         resourcePath() + "spaceship.png");
    mTextures.load(Textures::Hook,           resourcePath() + "hook.png");
    mTextures.load(Textures::Fuel,           resourcePath() + "fuel.png");
    mTextures.load(Textures::Enemy_1,        resourcePath() + "enemy1.png");
    mTextures.load(Textures::Enemy_2,        resourcePath() + "enemy2.png");
    mTextures.load(Textures::Bullet_1,       resourcePath() + "bullet.png");
    mTextures.load(Textures::Bullet_2,       resourcePath() + "bullet.png");
}
