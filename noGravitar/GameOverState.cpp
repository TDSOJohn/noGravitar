//
//  GameOverState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 20/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "GameOverState.hpp"
#include "Core/Utility.hpp"
#include "Player.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context):
    State(stack, context),
    mGameOverText(),
    mElapsedTime(sf::Time::Zero)
{
    sf::Font& font = context.fonts->get(Fonts::Mono);
    sf::Vector2f windowSize(context.window->getSize());

    mGameOverText.setFont(font);
    if (context.player->getMissionStatus() == Player::MissionFailure)
        mGameOverText.setString("Mission failed!");
    else
        mGameOverText.setString("Mission successful!");

    mGameOverText.setCharacterSize(70);
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    // Create dark, semitransparent background
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
    // Show state for 3 seconds, after return to menu
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(3))
    {
        requestStateClear();
        requestStackPush(States::Menu);
    }
    return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
    return false;
}
