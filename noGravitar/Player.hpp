//
//  Player.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 22/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

class Player
{
public:
    Player();
    
    void handleEvent(sf::Event event_in, );
    void handleRealTime(commands);
};

#endif /* Player_hpp */
