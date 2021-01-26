//
//  SceneNode.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef SceneNode_hpp
#define SceneNode_hpp

#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


#include "Command.hpp"



class SceneNode :   public sf::Transformable,
                    public sf::Drawable,
                    private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    
    
public:
                            SceneNode();
    void                    attachChild(Ptr child);
    Ptr                     detachChild(const SceneNode& node);
    
    void                    update(sf::Time dt);
    
    void                    onCommand(const Command& command, sf::Time dt);
    virtual unsigned int    getCategory() const;
    
    
private:
    virtual void            updateCurrent(sf::Time dt);
    void                    updateChildren(sf::Time dt);
    
    virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    
private:
    std::vector<Ptr>        mChildren;
    SceneNode*              mParent;
};



#endif /* Scenenode_hpp */
