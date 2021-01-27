//
//  World.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include <SFML/Graphics/View.hpp>


#include "World.hpp"


#include "Core/ResourcePath.hpp"
#include "Core/SpriteNode.hpp"


#include "Spaceship.hpp"



World::World(sf::RenderWindow& window) :
    mWindow(window),
    mView(sf::Vector2f(480.f, 300.f), sf::Vector2f(960.f, 600.f)),
    score(0)
{
    createTextures();
    loadScene();
}

void World::update(sf::Time dt)
{
    mSpaceship->setVelocity(0.f, 0.f);
    
    // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    
    adaptPlayerVelocity();
    
    mSceneGraph.update(dt);
    adaptPlayerPosition();

    mView.move(mSpaceship->getPosition() - mView.getCenter());
}

void World::draw()
{
    mWindow.setView(mView);
    mWindow.draw(mSceneGraph);
}


CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
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

void World::loadScene()
{
    //  Initialize the different layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        
        mSceneGraph.attachChild(std::move(layer));
    }
    
    //  Load background texture
    sf::Texture& texture = mTextures.get(Textures::ssBackground);
    
    //  Initialize the background
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
    //backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[DeepSpace]->attachChild(std::move(backgroundSprite));
    
    //  Initialize the player's spaceship
    std::unique_ptr<Spaceship> leader(new Spaceship(Spaceship::Old_Fart, mTextures));
    mSpaceship = leader.get();
    mSpaceship->setPosition(400, 400);
    mSceneLayers[Mission]->attachChild(std::move(leader));
}


void World::adaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, at least borderDistance units from the border
    sf::FloatRect mapBounds(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y);
    const float borderDistance = 40.f;
    
    sf::Vector2f position = mSpaceship->getPosition();
    position.x = std::max(position.x, mapBounds.left + borderDistance);
    position.x = std::min(position.x, mapBounds.left + mapBounds.width - borderDistance);
    position.y = std::max(position.y, mapBounds.top + borderDistance);
    position.y = std::min(position.y, mapBounds.top + mapBounds.height - borderDistance);
    mSpaceship->setPosition(position);
}


void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mSpaceship->getVelocity();
    
    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
        mSpaceship->setVelocity(velocity / std::sqrt(2.f));
}
