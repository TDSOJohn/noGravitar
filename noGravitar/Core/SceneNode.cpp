//
//  SceneNode.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "SceneNode.hpp"
#include "Category.hpp"



SceneNode::SceneNode() :
    mChildren(),
    mParent(nullptr)
{
    
}


void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}


SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) -> bool
    {
        return p.get() == &node;
    });
    
    assert(found != mChildren.end());
    
    Ptr result = std::move(*found);
    result -> mParent = nullptr;
    mChildren.erase(found);
    
    return result;
}


void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}


void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    // Command current node, if category matches
    if(command.category & getCategory())
        command.action(*this, dt);
    
    // Command children
    for(Ptr& child : mChildren)
        child->onCommand(command, dt);
    
}


unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}


void SceneNode::updateCurrent(sf::Time)
{
    // Do nothing by default
}


void SceneNode::updateChildren(sf::Time dt)
{
    for(Ptr& child : mChildren)
        child->update(dt);
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    drawCurrent(target, states);
    
    for (const Ptr& child : mChildren)
    {
        child->draw(target, states);
    }
}


void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
    // Do nothing by default
}
