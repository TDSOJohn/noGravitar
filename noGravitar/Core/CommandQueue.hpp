//
//  CommandQueue.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef CommandQueue_hpp
#define CommandQueue_hpp


#include <queue>


#include "Command.hpp"



class CommandQueue
{
public:
    void                            push(const Command& command);
    Command                         pop();
    bool                            isEmpty() const;
    
    
private:
    std::queue<Command>             mQueue;
};


#endif /* CommandQueue_hpp */
