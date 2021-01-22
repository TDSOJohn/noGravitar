//
//  Game.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


Game::Game() :
    mWindow(sf::VideoMode(Settings::MAP_X, Settings::MAP_Y), "Gravitar", sf::Style::Close),
    score(0),
    mWorld()
{    
    mFont.loadFromFile(resourcePath() + "andaleMono.ttf");
}


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);
        }
        
        updateStatistics(elapsedTime);
        render();
    }
}


void Game::processInput()
{
    CommandQueue& commands = mWorld.getCommandQueue();
    
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, commands);
        
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
    mPlayer.handleRealTimeInput(commands);
}


void Game::update(sf::Time elapsedTime)
{
    mWorld.update(elapsedTime);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    
    mWindow.display();
}


void Game::createTextures()
{
    textures->load(Textures::Won,           resourcePath() + "youWon.png");
    textures->load(Textures::Lost,          resourcePath() + "youLost.png");
    
    textures->load(Textures::ssBackground,  resourcePath() + "ssBackground.png");
    textures->load(Textures::pBackground,   resourcePath() + "pBackground.png");
    textures->load(Textures::Planet,        resourcePath() + "planet.png");
    textures->load(Textures::Eagle,         resourcePath() + "spaceship.png");
    textures->load(Textures::Raptor,        resourcePath() + "spaceship.png");
    textures->load(Textures::Hook,          resourcePath() + "hook.png");
    textures->load(Textures::Fuel,          resourcePath() + "fuel.png");
    textures->load(Textures::Enemy_1,       resourcePath() + "enemy1.png");
    textures->load(Textures::Enemy_2,       resourcePath() + "enemy2.png");
    textures->load(Textures::Bullet_1,      resourcePath() + "bullet.png");
    textures->load(Textures::Bullet_2,      resourcePath() + "bullet.png");
}
