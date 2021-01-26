//
//  Overlay.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Overlay.hpp"



Overlay::Overlay(TextureHolder& textures, Settings::gameStates* gState, int* scr) : youWonMessage(textures.get(Textures::Won)),
    youLostMessage(textures.get(Textures::Lost))
{
    score = scr;
    gameState = gState;
    if(!gameFont.loadFromFile(resourcePath() + "andaleMono.ttf"))
        return EXIT_FAILURE;
    
    scoreText.setString("SCORE");
    
    scoreText.setFont(gameFont);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setOrigin(scoreText.getLocalBounds().width/2, scoreText.getLocalBounds().height/2);

    scoreNumberText.setFont(gameFont);
    scoreNumberText.setCharacterSize(28);
    scoreNumberText.setFillColor(sf::Color::Green);
    scoreNumberText.setOrigin(scoreNumberText.getLocalBounds().width/2,
                              scoreNumberText.getLocalBounds().height/2);
    
    scoreText.setPosition(50.f, 100.f);
    scoreNumberText.setPosition(100.f, 94.f);

    youWonMessage.setOrigin(youWonMessage.getLocalBounds().width/2, youWonMessage.getLocalBounds().height/2);
    youWonMessage.setPosition(Settings::VIEW_X/2, Settings::VIEW_Y/2);

    youLostMessage.setOrigin(youLostMessage.getLocalBounds().width/2, youLostMessage.getLocalBounds().height/2);
    youLostMessage.setPosition(Settings::VIEW_X/2, Settings::VIEW_Y/2);
}


void Overlay::updateCurrent(sf::Time dt)
{
    scoreNumberText.setString(std::to_string(*score));
    scoreNumberText.setOrigin(scoreNumberText.getLocalBounds().width/2, scoreNumberText.getLocalBounds().height/2);
    scoreText.setPosition(50.f, 30.f);
    scoreNumberText.setPosition(100.f, 24.f);
}


void Overlay::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(scoreText);
    target.draw(scoreNumberText);
    if(*gameState == Settings::gameStates::Won)
        target.draw(youWonMessage);
    if(*gameState == Settings::gameStates::Lost)
        target.draw(youLostMessage);
}
