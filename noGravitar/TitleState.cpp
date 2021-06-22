//
//  TitleState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "TitleState.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context) :
    State(stack, context),
    mText(),
    mShowText(true),
    mTextEffectTime(sf::Time::Zero)
{
    Bar_1.setTexture(context.textures->get(Textures::TitleBar));
    Bar_2.setTexture(context.textures->get(Textures::TitleBar));
    Title.setTexture(context.textures->get(Textures::Title));

    sf::FloatRect bounds = Bar_1.getLocalBounds();
    Bar_1.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_1.setPosition(150.f, context.window->getView().getSize().y / 2.f);

    bounds = Bar_2.getLocalBounds();
    Bar_2.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Bar_2.setPosition(context.window->getView().getSize().x - 150.f, context.window->getView().getSize().y / 2.f);
    
    bounds = Title.getLocalBounds();
    Title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    Title.setPosition(context.window->getView().getSize() / 2.f - sf::Vector2f(0.f, 250.f));

    mText.setFont(context.fonts->get(Fonts::Mono));
    mText.setString("Press any key to start");
    
    bounds = mText.getLocalBounds();
    mText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mText.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(0.f, 100.f));
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(Bar_1);
    window.draw(Bar_2);
    
    window.draw(Title);
    
    if (mShowText)
        window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    
    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    
    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    
    return true;
}
