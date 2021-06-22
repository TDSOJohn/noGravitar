//
//  MenuState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 27/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "MenuState.hpp"

#include "Core/ResourceHolder.hpp"
#include "GUI/Button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>



MenuState::MenuState(StateStack& stack, Context context) :
    State(stack, context),
    mGUIContainer()
{
    //  Put vertical bars in place
    sf::Texture& texture = context.textures->get(Textures::TitleBar);
    Bar_1.setTexture(texture);
    sf::FloatRect bounds = Bar_1.getLocalBounds();
    Bar_1.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_1.setPosition(150.f, context.window->getView().getSize().y / 2.f);

    Bar_2.setTexture(texture);
    bounds = Bar_2.getLocalBounds();
    Bar_2.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_2.setPosition(context.window->getView().getSize().x - 150.f, context.window->getView().getSize().y / 2.f);

    //  A simple menu demonstration
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(300, 450);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->setPosition(300, 550);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this] ()
    {
        requestStackPush(States::Settings);
    });

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(300, 650);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(Bar_1);
    window.draw(Bar_2);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}
