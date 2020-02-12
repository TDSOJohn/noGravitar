//
//  Game.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Game.hpp"

Game::Game(const TextureHolder& textures) : solarSystem(textures), mainWindow(sf::VideoMode(Settings::MAP_X, Settings::MAP_Y), "Gravitar"),
mainView(sf::Vector2f(Settings::VIEW_X/2, Settings::VIEW_Y/2), sf::Vector2f(Settings::VIEW_X, Settings::VIEW_Y)), gameState(Settings::gameStates::Play)
{
    mainWindow.setVerticalSyncEnabled(true);
    TimePerFrame = sf::seconds(1.f / 60.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mainWindow.isOpen() && gameState == Settings::gameStates::Play)
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            if(!solarSystem.update(TimePerFrame))
                youLost();
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mainWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                solarSystem.handleInputEvent(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                solarSystem.handleInputEvent(event.key.code, false);
                break;
            case sf::Event::Closed:
                mainWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::render()
{
    mainWindow.clear();
    
    if(gameState == Settings::gameStates::Play)
    {
        mainWindow.draw(solarSystem);
    
        mainView.setCenter(solarSystem.getSpaceshipPosition());
        if(mainView.getCenter().x < Settings::VIEW_X/2)
            mainView.setCenter(Settings::VIEW_X/2, mainView.getCenter().y);
        if(mainView.getCenter().y < Settings::VIEW_Y/2)
            mainView.setCenter(mainView.getCenter().x, Settings::VIEW_Y/2);
        if(mainView.getCenter().x > (Settings::MAP_X - Settings::VIEW_X/2))
            mainView.setCenter((Settings::MAP_X - Settings::VIEW_X/2), mainView.getCenter().y);
        if(mainView.getCenter().y > (Settings::MAP_Y - Settings::VIEW_Y/2))
            mainView.setCenter(mainView.getCenter().x, (Settings::MAP_Y - Settings::VIEW_Y/2));
    }

    mainWindow.setView(mainView);
    mainWindow.display();
}

void Game::youLost()
{
    gameState = Settings::gameStates::Lost;
}
