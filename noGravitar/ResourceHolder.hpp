//
//  ResourceHolder.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void                    load(Identifier id, const std::string& filename);
    
    template <typename Parameter>
    void                    load(Identifier id, const std::string& filename, const Parameter& secondParam);
    
    Resource&               get(Identifier id);
    const Resource&         get(Identifier id) const;
    
private:
    void                    insertResource(Identifier id, std::unique_ptr<Resource> resource);
    
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#endif
