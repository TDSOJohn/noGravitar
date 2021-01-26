//
//  Player.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//


#include "Core/Settings.h"
#include "Core/Category.hpp"


#include "Spaceship.hpp"
#include "Player.hpp"



struct SpaceshipMover
{
    SpaceshipMover(float vx, float vy)
    : velocity(vx, vy)
    {
    }
    
    void operator() (Spaceship& spaceship, sf::Time) const
    {
        spaceship.setVelocity(spaceship.getVelocity() + velocity);
    }
    
    sf::Vector2f velocity;
};


Player::Player()
{
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right]= MoveRight;
    mKeyBinding[sf::Keyboard::Up]   = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;
    
    // Set initial action bindings
    initializeActions();
    
    // Assign all categories to player's aircraft
    for(auto& pair : mActionBinding)
        pair.second.category = Category::PlayerShip;
}

void Player::handleEvent(sf::Event event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for(auto pair : mKeyBinding)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(mActionBinding[pair.second]);
    }
}

void Player::assignKey(Actions action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
    {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }
    
    // Insert new binding
    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Actions action) const
{
    for(auto pair : mKeyBinding)
    {
        if (pair.second == action)
            return pair.first;
    }
    
    return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
    const float playerSpeed = 400.f;
    
    mActionBinding[MoveLeft].action = derivedAction<Spaceship>(SpaceshipMover(-playerSpeed, 0.f));
    mActionBinding[MoveRight].action= derivedAction<Spaceship>(SpaceshipMover(+playerSpeed, 0.f));
    mActionBinding[MoveUp].action   = derivedAction<Spaceship>(SpaceshipMover(0.f, -playerSpeed));
    mActionBinding[MoveDown].action = derivedAction<Spaceship>(SpaceshipMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Actions action)
{
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
            return true;
            
        default:
            return false;
    }
}
