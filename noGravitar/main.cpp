
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

#include "ResourcePath.hpp"
#include "Game.hpp"

int main()
{
    std::srand(std::time(0));
    TextureHolder textures;
    
    textures.load(Textures::youLost, resourcePath() + "youLost.png");
    
    textures.load(Textures::ssBackground, resourcePath() + "ssBackground.png");
    textures.load(Textures::pBackground, resourcePath() + "pBackground.png");
    textures.load(Textures::Planet, resourcePath() + "planet.png");
    textures.load(Textures::Spaceship, resourcePath() + "spaceship.png");
    textures.load(Textures::Hook, resourcePath() + "hook.png");
    textures.load(Textures::Fuel, resourcePath() + "fuel.png");
    textures.load(Textures::Enemy, resourcePath() + "enemy.png");
    textures.load(Textures::Bullet, resourcePath() + "bullet.png");
    
    Game game(textures);
    game.run();
    
    return EXIT_SUCCESS;
}
