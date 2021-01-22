//
//  World.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <array>
#include <queue>


#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>


#include "Core/ResourceHolder.hpp"
#include "Core/SceneNode.hpp"


#include "Overlay.hpp"



typedef std::unique_ptr<Overlay>        overlayPtr;


class World : private sf::NonCopyable
{
public:
    World();
    
    void                                update(sf::Time dt);
    
    void                                draw();
    
private:
    TextureHolder                       mTextures;
    overlayPtr                          gameOverlay;
    
    enum Layers
    {
        Mission,
        Space,
        DeepSpace,
        LayerCount
    };
    
    SceneNode                           mSceneGraph;
    
    std::array<SceneNode*, LayerCount>  mSceneLayers;

    
private:
    void                                createTextures();
    void                                loadScene();
};


#endif /* World_hpp */
