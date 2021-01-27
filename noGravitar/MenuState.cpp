//
//  MenuState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 27/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "MenuState.hpp"


#include "Core/ResourceHolder.hpp"


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>



MenuState::MenuState(StateStack& stack, Context context) :
    State(stack, context),
    mOptions(),
    mOptionIndex(0)
{
    sf::Texture& texture = context.textures->get(Textures::TitleBar);
    sf::Font& font = context.fonts->get(Fonts::Mono);
    
    Bar_1.setTexture(texture);
    sf::FloatRect bounds = Bar_1.getLocalBounds();
    Bar_1.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_1.setPosition(150.f, context.window->getView().getSize().y / 2.f);

    Bar_2.setTexture(texture);
    bounds = Bar_2.getLocalBounds();
    Bar_2.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_2.setPosition(context.window->getView().getSize().x - 150.f, context.window->getView().getSize().y / 2.f);

    // A simple menu demonstration
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    
    bounds = playOption.getLocalBounds();
    playOption.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);
    
    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");

    bounds = exitOption.getLocalBounds();
    exitOption.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);
   
    updateOptionText();
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    
    window.setView(window.getDefaultView());
    window.draw(Bar_1);
    window.draw(Bar_2);

    for(const sf::Text& text : mOptions)
        window.draw(text);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    // The demonstration menu logic
    if (event.type != sf::Event::KeyPressed)
        return false;
    
    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        else if (mOptionIndex == Exit)
        {
            // The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
            requestStackPop();
        }
    }
    
    else if (event.key.code == sf::Keyboard::Up)
    {
        // Decrement and wrap-around
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;
        
        updateOptionText();
    }
    
    else if (event.key.code == sf::Keyboard::Down)
    {
        // Increment and wrap-around
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;
        
        updateOptionText();
    }
    
    return true;
}

void MenuState::updateOptionText()
{
    if (mOptions.empty())
        return;
    
    // White all texts
    for(sf::Text& text : mOptions)
        text.setFillColor(sf::Color(0x18, 0x2E, 0x89));
    
    // Red the selected text
    mOptions[mOptionIndex].setFillColor(sf::Color::White);
}

