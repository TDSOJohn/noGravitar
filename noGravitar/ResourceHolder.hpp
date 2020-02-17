//
//  ResourceHolder.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef ResourceHolder_hpp
#define ResourceHolder_hpp

#include <iostream>
#include <cmath>
#include <map>
#include <SFML/Graphics.hpp>

#include "Settings.h"

/*
struct entityResources
{
    std::unique_ptr<sf::Texture> texture;
    characterSettings entityData;
};*/


class ResourceHolder
{
public:
    void                load(Textures::ID id, const std::string& filename);
    sf::Texture&        get(Textures::ID id);
    const sf::Texture&  get(Textures::ID id) const;
    
private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif
