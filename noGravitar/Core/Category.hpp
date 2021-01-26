//
//  Category.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Category_h
#define Category_h


// Entity/scene node category, used to dispatch commands
namespace Category
{
    enum Type
    {
        None                = 0,
        Scene               = 1 << 0,
        PlayerShip          = 1 << 1,
        AlliedShip          = 1 << 2,
        EnemyShip           = 1 << 3,
    };
}


#endif /* Category_h */
