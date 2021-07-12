//
//  World.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "World.hpp"
#include "Spaceship.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Core/Utility.hpp"

#include "Core/ResourcePath.hpp"
#include "Core/TextNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>


bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

//=============================


World::World(sf::RenderWindow& window, FontHolder& fonts) :
    mWindow(window),
    mFonts(fonts),
    mWorldView(window.getDefaultView()),
    mTextures(),
    mSceneGraph(),
    mSceneLayers(),
    mWorldBounds(0.f, 0.f, window.getSize().x, 4000.f),
    mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - (mWorldView.getSize().y / 2.f)),
    mPlayerSpaceship(nullptr),
    mEnemySpawnPoints(),
    mActiveEnemies()
{
    loadTextures();
    buildScene();
    
    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mPlayerSpaceship->setVelocity(0.f, 0.f);
    mWorldView.move(0.f, mPlayerSpaceship->getPosition().y - mWorldView.getCenter().y);

    // Setup commands to destroy entities and guide missiles
    destroyEntitiesOutsideView();
    guideMissiles();
    
    // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    adaptPlayerVelocity();

    // Collision detection and response (may destroy entities)
    handleCollisions();

    // Remove all destroyed entities, create new ones
    mSceneGraph.removeWrecks();
    spawnEnemies();

    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}


CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
    return !mPlayerSpaceship->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
    //  CHANGED
    // Player wins if all enemy spaceships are dead and player spaceship has reached a border
    return (mActiveEnemies.empty() && mEnemySpawnPoints.empty() && !mWorldBounds.contains(mPlayerSpaceship->getPosition()));
//    return !mWorldBounds.contains(mPlayerSpaceship->getPosition());
}

void World::loadTextures()
{
    mTextures.load(Textures::Won,           resourcePath() + "youWon.png");
    mTextures.load(Textures::Lost,          resourcePath() + "youLost.png");
    
    mTextures.load(Textures::Background,    resourcePath() + "Background.png");
    mTextures.load(Textures::Planet,        resourcePath() + "planet.png");
    mTextures.load(Textures::Eagle,         resourcePath() + "spaceship.png");
    mTextures.load(Textures::Raptor,        resourcePath() + "spaceship.png");
    mTextures.load(Textures::Hook,          resourcePath() + "hook.png");
    mTextures.load(Textures::Fuel,          resourcePath() + "fuel.png");
    mTextures.load(Textures::Enemy_1,       resourcePath() + "enemy1.png");
    mTextures.load(Textures::Enemy_2,       resourcePath() + "enemy2.png");
    mTextures.load(Textures::Bullet_1,      resourcePath() + "bullet_1.png");
    mTextures.load(Textures::Bullet_2,      resourcePath() + "bullet_2.png");
    mTextures.load(Textures::Bullet_3,      resourcePath() + "bullet_3.png");
}

void World::adaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, at least borderDistance units from the border
    sf::FloatRect viewBounds = getViewBounds();
    const float borderDistance = 40.f;
    
    sf::Vector2f position = mPlayerSpaceship->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerSpaceship->setPosition(position);
}


void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayerSpaceship->getVelocity();
    
    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerSpaceship->setVelocity(velocity / std::sqrt(2.f));
    
    //  Add scrolling velocity
    //  mPlayerSpaceship->accelerate(0.f, mScrollSpeed);
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(auto pair : collisionPairs)
    {
        if(matchesCategories(pair, Category::PlayerShip, Category::EnemyShip))
        {
            auto& player = static_cast<Spaceship&>(*pair.first);
            auto& enemy = static_cast<Spaceship&>(*pair.second);

            // Collision: Player damage = enemy's remaining HP
            player.damage(enemy.getHitpoints());
            enemy.destroy();
        }

        else if(matchesCategories(pair, Category::PlayerShip, Category::Pickup))
        {
            auto& player = static_cast<Spaceship&>(*pair.first);
            auto& pickup = static_cast<Pickup&>(*pair.second);

            // Apply pickup effect to player, destroy projectile
            pickup.apply(player);
            pickup.destroy();
        }

        else if(matchesCategories(pair, Category::EnemyShip, Category::AlliedProjectile)
              || matchesCategories(pair, Category::PlayerShip, Category::EnemyProjectile))
        {
            auto& spaceship = static_cast<Spaceship&>(*pair.first);
            auto& projectile = static_cast<Projectile&>(*pair.second);

            // Apply projectile damage to aircraft, destroy projectile
            spaceship.damage(projectile.getDamage());
            projectile.destroy();
        }
    }

}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Space) ? Category::Scene : Category::None;

        SceneNode::Ptr layer(new SceneNode(category));
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[DeepSpace]->attachChild(std::move(backgroundSprite));

    // Add player's spaceship
    std::unique_ptr<Spaceship> player(new Spaceship(Spaceship::Speed_Junkie, mTextures, mFonts));
    mPlayerSpaceship = player.get();
    mPlayerSpaceship->setPosition(mSpawnPosition);
    mSceneLayers[Space]->attachChild(std::move(player));

    // Add enemy aircraft
    addEnemies();
}

void World::addEnemies()
{
    int spawn_x, spawn_y;
    spawn_x = spawn_y = 0;
    // Add enemies to the spawn point container
    for(int i = 0; i < 6; i++)
    {
        spawn_x = randomInt(mWorldBounds.width - 300);
        spawn_y = randomInt(mWorldBounds.height - 900) + 300;
        addEnemy(Spaceship::Enemy_1, spawn_x, spawn_y);
    }
    for(int i = 0; i < 5; i++)
    {
        spawn_x = randomInt(mWorldBounds.width - 600);
        spawn_y = randomInt(mWorldBounds.height - 900) + 300;
        addEnemy(Spaceship::Enemy_2, spawn_x, spawn_y);
    }

    // Sort all enemies according to their y value, such that lower enemies are checked first for spawning
    std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
    {
        return lhs.y < rhs.y;
    });
}

void World::addEnemy(Spaceship::Type type, float relX, float relY)
{
    //  CHANGED WTF was the shitty coordinates system?!
    SpawnPoint spawn(type, relX, relY);
    mEnemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
    // Spawn all enemies entering the view area (including distance) this frame
    while (!mEnemySpawnPoints.empty()
        && mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();
        
        std::unique_ptr<Spaceship> enemy(new Spaceship(spawn.type, mTextures, mFonts));
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);

        mSceneLayers[Space]->attachChild(std::move(enemy));

        // Enemy is spawned, remove from the list to spawn
        mEnemySpawnPoints.pop_back();
    }
}

void World::destroyEntitiesOutsideView()
{
    //  CHANGED: NOW NOT APPLYING TO ENEMY SHIPS
    Command command;
    command.category = Category::Projectile;// | Category::EnemyShip;
    command.action = derivedAction<GameEntity>([this] (GameEntity& e, sf::Time)
    {
        if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
            e.destroy();
    });

    mCommandQueue.push(command);
}

void World::guideMissiles()
{
    Command enemyCollector;
    enemyCollector.category = Category::EnemyShip;
    enemyCollector.action = derivedAction<Spaceship>([this] (Spaceship& enemy, sf::Time)
    {
        if(!enemy.isDestroyed())
            mActiveEnemies.push_back(&enemy);
    });
    
    Command missileGuider;
    missileGuider.category = Category::AlliedProjectile;
    missileGuider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time)
    {
        if(!missile.isGuided())
            return;
        
        float minDistance = std::numeric_limits<float>::max();
        Spaceship* closestEnemy = nullptr;
        
        for(auto* enemy: mActiveEnemies)
        {
            float enemyDistance = distance(missile, *enemy);
            if(enemyDistance < minDistance)
            {
                closestEnemy = enemy;
                minDistance = enemyDistance;
            }
        }
        if(closestEnemy)
            missile.guideTowards(closestEnemy->getPosition());
    });
    
    mCommandQueue.push(enemyCollector);
    mCommandQueue.push(missileGuider);
    mActiveEnemies.clear();
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
    // Return view bounds + some area at top, where enemies spawn
    sf::FloatRect bounds = getViewBounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;

    return bounds;
}
