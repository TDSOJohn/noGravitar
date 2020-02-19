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
    entityResources er;
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename))
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    er.texture = std::move(texture);
    if(id == Textures::Bullet_1)
        er.entityData =Settings::BULLET_1;
    
    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(er)));
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
