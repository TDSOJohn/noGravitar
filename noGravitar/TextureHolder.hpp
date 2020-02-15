//
//  TextureHolder.hpp
//  Grativar_final
//
//  Created by Giovanni Basso on 24/01/2020.
//  Copyright © 2020 Giovanni Basso. All rights reserved.
//

#ifndef TextureHolder_hpp
#define TextureHolder_hpp

#include <map>

#include <SFML/Graphics.hpp>

namespace Textures
{
    enum ID { ssBackground, pBackground, Planet, Spaceship, Hook, Fuel, Enemy, Bullet, youLost };
}

class TextureHolder
{
public:
    void                load(Textures::ID id, const std::string& filename);
    sf::Texture&        get(Textures::ID id);
    const sf::Texture&  get(Textures::ID id) const;
    
private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif
