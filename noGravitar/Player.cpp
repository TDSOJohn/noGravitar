//
//  Player.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "Player.hpp"
#include "Spaceship.hpp"
#include "Core/CommandQueue.hpp"


struct SpaceshipMover
{
    SpaceshipMover(float vx, float vy)
    : velocity(vx, vy)
    {
    }
    
    void operator() (Spaceship& spaceship, sf::Time) const
    {
        spaceship.accelerate(velocity * spaceship.getMaxSpeed());
    }
    
    sf::Vector2f velocity;
};


Player::Player():
    mCurrentMissionStatus(MissionRunning)
{
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::W]    = MoveUp;
    mKeyBinding[sf::Keyboard::A]    = MoveLeft;
    mKeyBinding[sf::Keyboard::S]    = MoveDown;
    mKeyBinding[sf::Keyboard::D]    = MoveRight;
    mKeyBinding[sf::Keyboard::K]    = Fire;
    mKeyBinding[sf::Keyboard::Space]= UseHook;
    mKeyBinding[sf::Keyboard::M]    = LaunchMissile;

    // Set initial action bindings
    initializeActions();
    
    // Assign all categories to player's aircraft
    for(auto& pair : mActionBinding)
        pair.second.category = Category::PlayerShip;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
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

void Player::assignKey(Action action, sf::Keyboard::Key key)
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

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for(auto pair : mKeyBinding)
    {
        if (pair.second == action)
            return pair.first;
    }
    
    return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
    mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
    return mCurrentMissionStatus;
}

void Player::initializeActions()
{
    mActionBinding[MoveLeft].action = derivedAction<Spaceship>(SpaceshipMover(-1, 0.f));
    mActionBinding[MoveRight].action= derivedAction<Spaceship>(SpaceshipMover(+1, 0.f));
    mActionBinding[MoveUp].action   = derivedAction<Spaceship>(SpaceshipMover(0.f, -1));
    mActionBinding[MoveDown].action = derivedAction<Spaceship>(SpaceshipMover(0.f, +1));
    mActionBinding[Fire].action = derivedAction<Spaceship>(std::bind(&Spaceship::fire, std::placeholders::_1));
    mActionBinding[LaunchMissile].action = derivedAction<Spaceship>(std::bind(&Spaceship::launchMissile, std::placeholders::_1));
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
        case Fire:
            return true;
            
        default:
            return false;
    }
}
