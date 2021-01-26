//
//  Player.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp


#include <map>


#include <SFML/Window/Event.hpp>


#include "Core/Command.hpp"
#include "Core/CommandQueue.hpp"



class CommandQueue;


class Player
{
public:
    enum Actions
    {
        MoveLeft,
        MoveUp,
        MoveRight,
        MoveDown,
        Shoot,
        UseHook,
        ActionsCount
    };

    Player();
    
    void                            handleEvent(sf::Event event, CommandQueue& commands);
    void                            handleRealTimeInput(CommandQueue& commands);

    void                            assignKey(Actions action, sf::Keyboard::Key key);
    sf::Keyboard::Key               getAssignedKey(Actions action) const;
    
    
private:
    void                            initializeActions();
    static bool                     isRealtimeAction(Actions action);
    
    
private:
    std::map<sf::Keyboard::Key, Actions>
                                    mKeyBinding;
    std::map<Actions, Command>      mActionBinding;
    
};

#endif /* Player_hpp */
