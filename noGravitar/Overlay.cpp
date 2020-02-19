//
//  Overlay.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Overlay.hpp"

Overlay::Overlay(Settings::gameStates* gState, int* scr, const ResourceHolder& resources) : youWonMessage(*(resources.get(Textures::Won).texture)), youLostMessage(*(resources.get(Textures::Lost).texture))
{
    score = scr;
    gameState = gState;
    if(!gameFont.loadFromFile(resourcePath() + "andaleMono.ttf"))
        return EXIT_FAILURE;
    scoreText.setString("SCORE");
    scoreText.setFont(gameFont);
    scoreNumberText.setFont(gameFont);
    scoreText.setCharacterSize(20);
    scoreNumberText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::Green);
    scoreNumberText.setFillColor(sf::Color::Green);
    scoreText.setOrigin(scoreText.getLocalBounds().width/2, scoreText.getLocalBounds().height/2);
    
    youWonMessage.setOrigin(youWonMessage.getLocalBounds().width/2, youWonMessage.getLocalBounds().height/2);
    youWonMessage.setPosition(Settings::VIEW_X/2, Settings::VIEW_Y/2);
    youLostMessage.setOrigin(youLostMessage.getLocalBounds().width/2, youLostMessage.getLocalBounds().height/2);
    youLostMessage.setPosition(Settings::VIEW_X/2, Settings::VIEW_Y/2);
}

void Overlay::update(sf::Vector2f position)
{
    scoreNumberText.setString(std::to_string(*score));
    scoreNumberText.setOrigin(scoreNumberText.getLocalBounds().width/2, scoreNumberText.getLocalBounds().height/2);
    scoreText.setPosition(position - sf::Vector2f(0.f, 285.f));
    scoreNumberText.setPosition(position - sf::Vector2f(0.f, 255.f));
}
