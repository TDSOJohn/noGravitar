//
//  Player.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Core/Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
public:
    enum Action
    {
        MoveUp,
        MoveLeft,
        MoveDown,
        MoveRight,
        Fire,
        UseHook,
        LaunchMissile,
        ActionCount
    };

    enum MissionStatus
    {
        MissionRunning,
        MissionSuccess,
        MissionFailure
    };

    Player();
    
    void                            handleEvent(const sf::Event& event, CommandQueue& commands);
    void                            handleRealTimeInput(CommandQueue& commands);

    void                            assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key               getAssignedKey(Action action) const;
    
    void                            setMissionStatus(MissionStatus status);
    MissionStatus                   getMissionStatus() const;

private:
    void                            initializeActions();
    static bool                     isRealtimeAction(Action action);
    
    
private:
    std::map<sf::Keyboard::Key, Action>
                                    mKeyBinding;
    std::map<Action, Command>       mActionBinding;
    MissionStatus                   mCurrentMissionStatus;

};

#endif /* Player_hpp */
