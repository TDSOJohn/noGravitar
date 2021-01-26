//
//  Overlay.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 16/02/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef Overlay_hpp
#define Overlay_hpp

#include "Core/ResourcePath.hpp"
#include "Core/ResourceHolder.hpp"


#include "Core/GameEntity.hpp"



class Overlay : public GameEntity
{
public:
    Overlay(TextureHolder& textures, Settings::gameStates*, int*);
    
    void                    updateCurrent(sf::Time dt);
    
    
private:
    int*                    score;
    Settings::gameStates*   gameState;
    
    sf::Font                gameFont;
    sf::Text                scoreText;
    sf::Text                scoreNumberText;
    
    sf::Sprite              youWonMessage;
    sf::Sprite              youLostMessage;
    
    
private:
    void                    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
};
#endif /* Overlay_hpp */
