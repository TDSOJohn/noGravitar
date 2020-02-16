//
//  Overlay.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "Overlay.hpp"

Overlay::Overlay(Settings::gameStates* gState, int* scr, const TextureHolder& textures) : youWonMessage(textures.get(Textures::youWon)), youLostMessage(textures.get(Textures::youLost))
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
}

Overlay::~Overlay()
{
    
}

void Overlay::update(sf::Vector2f position)
{
    scoreNumberText.setString(std::to_string(*score));
    scoreNumberText.setOrigin(scoreNumberText.getLocalBounds().width/2, scoreNumberText.getLocalBounds().height/2);
    scoreText.setPosition(position - sf::Vector2f(0.f, 285.f));
    scoreNumberText.setPosition(position - sf::Vector2f(0.f, 255.f));
}
