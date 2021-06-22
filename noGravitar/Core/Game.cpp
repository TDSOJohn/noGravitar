//
//  Game.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//


#include "Game.hpp"
#include "Utility.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourcePath.hpp"

#include "../TitleState.hpp"
#include "../GameState.hpp"
#include "../MenuState.hpp"
#include "../PauseState.hpp"
#include "../SettingsState.hpp"
#include "../GameOverState.hpp"


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


Game::Game() :
    mWindow(sf::VideoMode(1000, 3000), "Gravitar", sf::Style::Close),
    mTextures(),
    mFonts(),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)),
    mStatisticsText(),
    mStatisticsUpdateTime(),
    mStatisticsNumFrames(0)
{
    mWindow.setKeyRepeatEnabled(false);
    
    mFonts.load(Fonts::Mono, resourcePath() + "andaleMono.ttf");
    
    mTextures.load(Textures::TitleBar,      resourcePath() + "TitleBar.png");
    mTextures.load(Textures::Title,         resourcePath() + "Title.png");
    mTextures.load(Textures::ButtonN,         resourcePath() + "Button_128_normal.png");
    mTextures.load(Textures::ButtonP,         resourcePath() + "Button_128_pressed.png");
    mTextures.load(Textures::ButtonS,         resourcePath() + "Button_128_selected.png");

    mStatisticsText.setFont(mFonts.get(Fonts::Mono));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(20u);
    
    registerStates();
    mStateStack.pushState(States::Title);
}


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            
            processInput();
            update(TimePerFrame);
            
            if(mStateStack.isEmpty())
                mWindow.close();
        }
        
        updateStatistics(dt);
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
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}


void Game::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<GameOverState>(States::GameOver);
}
