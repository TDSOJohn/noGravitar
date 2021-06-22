//
//  TextNode.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 10/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "TextNode.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

    
TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
    mText.setFont(fonts.get(Fonts::Mono));
    mText.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}
