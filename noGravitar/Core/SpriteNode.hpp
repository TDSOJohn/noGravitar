//
//  SpriteNode.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef SpriteNode_hpp
#define SpriteNode_hpp

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public SceneNode
{
public:
    explicit            SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    
    
private:
    sf::Sprite            mSprite;


private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif /* SpriteNode_hpp */
