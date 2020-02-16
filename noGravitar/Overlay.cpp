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
    scoreText.setFont(gameFont);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::Green);
}

Overlay::~Overlay()
{
    
}

void Overlay::update(sf::Vector2f position)
{
    scoreText.setString(std::to_string(*score));
    scoreText.setPosition(position - sf::Vector2f(0.f, 250.f));
}
