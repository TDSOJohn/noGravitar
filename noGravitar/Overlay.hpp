//
//  Overlay.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Overlay_hpp
#define Overlay_hpp

#include "ResourcePath.hpp"
#include "ResourceHolder.hpp"

class Overlay : public sf::Drawable
{
public:
    Overlay(Settings::gameStates*, int*, const ResourceHolder& = ResourceHolder());

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
        target.draw(scoreText);
        target.draw(scoreNumberText);
        if(*gameState == Settings::gameStates::Won)
            target.draw(youWonMessage);
        if(*gameState == Settings::gameStates::Lost)
            target.draw(youLostMessage);
    }
};
#endif /* Overlay_hpp */
