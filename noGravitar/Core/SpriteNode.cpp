//
//  SpriteNode.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "SpriteNode.hpp"


#include <SFML/Graphics/RenderTarget.hpp>



SpriteNode::SpriteNode(const sf::Texture& texture) :
    mSprite(texture)
{
}


SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) :
    mSprite(texture, textureRect)
{
}


void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
