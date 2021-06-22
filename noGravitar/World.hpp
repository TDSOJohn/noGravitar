//
//  World.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include "Core/ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Core/SceneNode.hpp"
#include "Core/SpriteNode.hpp"
#include "Core/Command.hpp"
#include "Core/CommandQueue.hpp"
#include "Spaceship.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <array>
#include <queue>


namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
    explicit                            World(sf::RenderWindow& window, FontHolder& fonts);
    
    void                                update(sf::Time dt);
    void                                draw();
    
    CommandQueue&                       getCommandQueue();
    
    bool                                hasAlivePlayer() const;
    bool                                hasPlayerReachedEnd() const;

private:
    enum Layers
    {
        DeepSpace,
        Space,
        LayerCount
    };

    struct SpawnPoint
    {
        //  Spawn point for enemy spaceships
        SpawnPoint(Spaceship::Type type, float x, float y):
            type(type),
            x(x),
            y(y)
        {
        }

        Spaceship::Type type;
        float x;
        float y;
    };

    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    
    TextureHolder                       mTextures;
    FontHolder&                         mFonts;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    CommandQueue                        mCommandQueue;
    
    sf::FloatRect                       mWorldBounds;
    sf::Vector2f                        mSpawnPosition;
    float                               mScrollSpeed; //Useless?
    Spaceship*                          mPlayerSpaceship;

    std::vector<SpawnPoint>             mEnemySpawnPoints;
    std::vector<Spaceship*>             mActiveEnemies;

private:
    void                                loadTextures();
    void                                buildScene();
    
    void                                adaptPlayerPosition();
    void                                adaptPlayerVelocity();
    void                                handleCollisions();

    void                                addEnemies();
    void                                addEnemy(Spaceship::Type type, float relX, float relY);
    void                                spawnEnemies();
    void                                destroyEntitiesOutsideView();
    void                                guideMissiles();
    sf::FloatRect                       getViewBounds() const;
    sf::FloatRect                       getBattlefieldBounds() const;
};


#endif /* World_hpp */
