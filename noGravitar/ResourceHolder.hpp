//
//  ResourceHolder.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef ResourceHolder_hpp
#define ResourceHolder_hpp

#include <map>
#include <SFML/Graphics.hpp>

#include "Settings.h"

struct entityResources
{
    std::unique_ptr<sf::Texture> texture;
    characterSettings entityData;
};

namespace Textures
{
    enum                ID { ssBackground, pBackground, Planet, Spaceship, Hook, Fuel, Enemy, Bullet };
}

class ResourceHolder
{
public:
    void                load(Textures::ID id, const std::string& filename);
    entityResources&    get(Textures::ID id);
    const entityResources& get(Textures::ID id) const;
    
private:
    std::map<Textures::ID, entityResources> mTextureMap;
};

#endif
