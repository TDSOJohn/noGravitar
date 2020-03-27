//
//  Overlay.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Overlay_hpp
#define Overlay_hpp

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "ResourcePath.hpp"
#include "ResourceHolder.hpp"

class Overlay : public sf::Drawable
{
public:
    Overlay(Settings::gameStates*, int*, const ResourceHolder<sf::Texture, Textures::ID>& = ResourceHolder<sf::Texture, Textures::ID>());

    void                    update(sf::Vector2f);
    
private:
    int*                    score;
    Settings::gameStates*   gameState;
    
    sf::Font                gameFont;
    sf::Text                scoreText;
    sf::Text                scoreNumberText;
    
    sf::Sprite              youWonMessage;
    sf::Sprite              youLostMessage;
    
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(scoreText, states);
        target.draw(scoreNumberText, states);
        if(*gameState == Settings::gameStates::Won)
            target.draw(youWonMessage, states);
        if(*gameState == Settings::gameStates::Lost)
            target.draw(youLostMessage, states);
    }
};
#endif /* Overlay_hpp */
