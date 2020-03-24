
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "ResourcePath.hpp"
#include "ResourceHolder.hpp"
#include "Game.hpp"

int main()
{
    std::srand(std::time(0));
    ResourceHolder<sf::Texture, Textures::ID> textures;

    textures.load(Textures::Won, resourcePath() + "youWon.png");
    textures.load(Textures::Lost, resourcePath() + "youLost.png");
        
    textures.load(Textures::ssBackground, resourcePath() + "ssBackground.png");
    textures.load(Textures::pBackground, resourcePath() + "pBackground.png");
    textures.load(Textures::Planet, resourcePath() + "planet.png");
    textures.load(Textures::Spaceship, resourcePath() + "spaceship.png");
    textures.load(Textures::Hook, resourcePath() + "hook.png");
    textures.load(Textures::Fuel, resourcePath() + "fuel.png");
    textures.load(Textures::Enemy_1, resourcePath() + "enemy1.png");
    textures.load(Textures::Enemy_2, resourcePath() + "enemy2.png");
    textures.load(Textures::Bullet_1, resourcePath() + "bullet.png");
    textures.load(Textures::Bullet_2, resourcePath() + "bullet.png");
    
    Game game(textures);
    game.run();
    
    return EXIT_SUCCESS;
}
