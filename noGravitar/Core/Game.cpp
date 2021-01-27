//
//  Game.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//


#include "ResourcePath.hpp"
#include "Game.hpp"


#include "../GameState.hpp"
#include "../PauseState.hpp"
#include "../TitleState.hpp"
#include "../MenuState.hpp"



const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


Game::Game() :
    mWindow(sf::VideoMode(Settings::MAP_X, Settings::MAP_Y), "Gravitar", sf::Style::Close),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{    
    mFonts.load(Fonts::Mono, resourcePath() + "andaleMono.ttf");
    
    mTextures.load(Textures::TitleBar,      resourcePath() + "TitleBar.png");
    mTextures.load(Textures::Title,         resourcePath() + "Title.png");

    registerStates();
    mStateStack.pushState(States::Title);
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
            
            if(mStateStack.isEmpty())
                mWindow.close();
        }
        
        updateStatistics(elapsedTime);
        render();
    }
}


void Game::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
        
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}


void Game::update(sf::Time dt)
{
    mStateStack.update(dt);
}


void Game::render()
{
    mWindow.clear();
    
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    
    mWindow.display();
}


void Game::updateStatistics(sf::Time dt)
{
    
}


void Game::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
}
