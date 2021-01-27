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
#include "Core/CommandQueue.hpp"


#include "Spaceship.hpp"



class World : private sf::NonCopyable
{
public:
    explicit                            World(sf::RenderWindow& window);
    
    void                                update(sf::Time dt);
    void                                draw();
    
    CommandQueue&                       getCommandQueue();
    
    
private:
    enum Layers
    {
        DeepSpace,
        Space,
        Mission,
        Info,
        LayerCount
    };

    sf::RenderWindow&                   mWindow;
    sf::View                            mView;
    
    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    CommandQueue                        mCommandQueue;
    
    TextureHolder                       mTextures;
    
    Spaceship*                          mSpaceship;
    int                                 score;
    
private:
    void                                createTextures();
    void                                loadScene();
    
    void                                adaptPlayerPosition();
    void                                adaptPlayerVelocity();
};


#endif /* World_hpp */
