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

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void                load(Identifier id, const std::string& filename);
    
    template <typename Parameter>
    void                load(Identifier id, const std::string& filename, const Parameter& secondParam);
    
    Resource&           get(Identifier id);
    const Resource&     get(Identifier id) const;
    
private:
    void                insertResource(Identifier id, std::unique_ptr<Resource> resource);
private:
    //  std::unique_ptr for automatic deletion on pointer out of scope
    //  or unique_ptr assignement to other pointer
    //  ownership is transferred, never shared
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#endif
