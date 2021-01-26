//
//  CommandQueue.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 23/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "CommandQueue.hpp"



void CommandQueue::push(const Command& command)
{
    mQueue.push(command);
}


Command CommandQueue::pop()
{
    Command command = mQueue.front();
    mQueue.pop();
    return command;
}


bool CommandQueue::isEmpty() const
{
    return mQueue.empty();
}
