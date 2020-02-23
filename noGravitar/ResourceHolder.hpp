//
//  ResourceHolder.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void                    load(Identifier, const std::string&);
    
    template <typename Parameter>
    void                    load(Identifier, const std::string&, const Parameter&);
    
    Resource&               get(Identifier);
    const Resource&         get(Identifier) const;
    
private:
    void                    insertResource(Identifier, std::unique_ptr<Resource>);
    
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#endif
