#include "ResourceHolder.hpp"

namespace ah
{

ResourceHolder::ResourceHolder()
{
}

sf::SoundBuffer& ResourceHolder::getSoundBuffer(std::string const& filename)
{
    return mSoundBuffers.acquire(filename,thor::Resources::fromFile<sf::SoundBuffer>(filename),thor::Resources::Reuse);
}

sf::Font& ResourceHolder::getFont(std::string const& filename)
{
    return mFonts.acquire(filename,thor::Resources::fromFile<sf::Font>(filename),thor::Resources::Reuse);
}

sf::Image& ResourceHolder::getImage(std::string const& filename)
{
    return mImages.acquire(filename,thor::Resources::fromFile<sf::Image>(filename),thor::Resources::Reuse);
}

sf::Texture& ResourceHolder::getTexture(std::string const& filename)
{
    return mTextures.acquire(filename,thor::Resources::fromFile<sf::Texture>(filename),thor::Resources::Reuse);
}

}
