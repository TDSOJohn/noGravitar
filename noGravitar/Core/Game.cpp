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
    mWorld(mWindow)
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


void Game::update(sf::Time dt)
{
    mWorld.update(dt);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    
    mWindow.display();
}

void Game::updateStatistics(sf::Time dt)
{
    
}
