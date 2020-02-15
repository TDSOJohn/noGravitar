//
//  Game.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Game.hpp"

Game::Game(const TextureHolder& txtrs) : mainWindow(sf::VideoMode(Settings::MAP_X, Settings::MAP_Y), "Gravitar"),
mainView(sf::Vector2f(Settings::VIEW_X/2, Settings::VIEW_Y/2), sf::Vector2f(Settings::VIEW_X, Settings::VIEW_Y)), gameState(Settings::gameStates::Play), youWonMessage(txtrs.get(Textures::youWon)), youLostMessage(txtrs.get(Textures::youLost))
{
    textures = &txtrs;
    solarSystem = new SolarSystem(*textures);
    mainWindow.setVerticalSyncEnabled(true);
    TimePerFrame = sf::seconds(1.f / 60.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mainWindow.isOpen())
    {
        processEvents();
        
        if(gameState == Settings::gameStates::Play)
        {
            gameState = solarSystem->update(TimePerFrame);
            if(gameState == Settings::gameStates::Lost)
                youLost();
        }
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mainWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mainWindow.close();
        switch(gameState)
        {
            case Settings::gameStates::Play:
                if(event.type == sf::Event::KeyPressed)
                    solarSystem->handleInputEvent(event.key.code, true);
                if(event.type == sf::Event::KeyReleased)
                    solarSystem->handleInputEvent(event.key.code, false);
                break;
            case Settings::gameStates::Pause:
                break;
            default:                        //Cases Lost e Won
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)    //start a new match if you lost and you hit (or released) 'n'
                {
                    solarSystem = new SolarSystem(*textures);
                    gameState = Settings::gameStates::Play;
                }
                break;
        }
    }
}

void Game::render()
{
    mainWindow.clear();
    
    if(gameState == Settings::gameStates::Play)
    {
        mainWindow.draw(*solarSystem);
    
        mainView.setCenter(solarSystem->getSpaceshipPosition());
        if(mainView.getCenter().x < Settings::VIEW_X/2)
            mainView.setCenter(Settings::VIEW_X/2, mainView.getCenter().y);
        if(mainView.getCenter().y < Settings::VIEW_Y/2)
            mainView.setCenter(mainView.getCenter().x, Settings::VIEW_Y/2);
        if(mainView.getCenter().x > (Settings::MAP_X - Settings::VIEW_X/2))
            mainView.setCenter((Settings::MAP_X - Settings::VIEW_X/2), mainView.getCenter().y);
        if(mainView.getCenter().y > (Settings::MAP_Y - Settings::VIEW_Y/2))
            mainView.setCenter(mainView.getCenter().x, (Settings::MAP_Y - Settings::VIEW_Y/2));
    }
    else if(gameState == Settings::gameStates::Won)
    {
        mainView.setCenter(Settings::VIEW_X/2, Settings::VIEW_Y/2);
        mainWindow.draw(youWonMessage);
    }
    else if (gameState == Settings::gameStates::Lost)
    {
        mainView.setCenter(Settings::VIEW_X/2, Settings::VIEW_Y/2);
        mainWindow.draw(youLostMessage);
    }

    mainWindow.setView(mainView);
    mainWindow.display();
}

void Game::youWon()
{
    std::cout << "you have won!" << std::endl;
    std::cout << gameState << std::endl;
    delete solarSystem;
    solarSystem = nullptr;
}

void Game::youLost()
{
    std::cout << "you have lost!" << std::endl;
    std::cout << gameState << std::endl;
    delete solarSystem;
    solarSystem = nullptr;
}
