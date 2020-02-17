//
//  TextureHolder.cpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#include "ResourceHolder.hpp"

void ResourceHolder::load(Textures::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename))
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    entityResources c = { std::move(texture), Settings::ENEMY_1 };
    
    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(c)));
    assert(inserted.second);
}

entityResources& ResourceHolder::get(Textures::ID id)
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());
    
    return found->second;
}

const entityResources& ResourceHolder::get(const Textures::ID id) const
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());
    
    return found->second;
}
