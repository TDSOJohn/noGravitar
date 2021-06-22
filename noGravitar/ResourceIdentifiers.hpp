//
//  ResourceIdentifiers.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 14/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef ResourceIdentifiers_h
#define ResourceIdentifiers_h

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        TitleBar,
        Title,
        
        ssBackground,
        pBackground,
        Planet,
        Raptor,
        Eagle,
        Hook,
        Fuel,
        Enemy_1,
        Enemy_2,
        Bullet_1,
        Bullet_2,
        Bullet_3,
        Won,
        Lost,
        ButtonN,
        ButtonP,
        ButtonS,
    };
}

namespace Fonts
{
    enum ID
    {
        Mono,
        Cursive,
        Standard
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>   TextureHolder;

typedef ResourceHolder<sf::Font, Fonts::ID>         FontHolder;


#endif /* ResourceIdentifiers_h */
