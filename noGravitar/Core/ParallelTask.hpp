//
//  ParallelTask.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef ParallelTask_hpp
#define ParallelTask_hpp


#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>



class ParallelTask
{
public:
                                ParallelTask();
    void                        execute();
    bool                        isFinished();
    float                       getCompletion();
    
private:
    void                        runTask();
    
private:
    sf::Thread                  mThread;
    bool                        mFinished;
    sf::Clock                   mElapsedTime;
    sf::Mutex                   mMutex;
};


#endif /* ParallelTask_hpp */
