#include "ResourceHolder.hpp"

namespace ah
{

ResourceHolder::ResourceHolder()
{
}

sf::SoundBuffer& ResourceHolder::getSoundBuffer(std::string const& filename, std::string const& id)
{
    if (id != "")
    {
        assert(mSoundBuffers[id].loadFromFile(filename));
        return mSoundBuffers.at(id);
    }
    else if (mSoundBuffers.find(filename) == mSoundBuffers.end())
    {
        assert(mSoundBuffers[filename].loadFromFile(filename));
    }
    return mSoundBuffers.at(filename);
}

sf::Font& ResourceHolder::getFont(std::string const& filename, std::string const& id)
{
    if (id != "")
    {
        assert(mFonts[id].loadFromFile(filename));
        return mFonts.at(id);
    }
    else if (mFonts.find(filename) == mFonts.end())
    {
        assert(mFonts[filename].loadFromFile(filename));
    }
    return mFonts.at(filename);
}

sf::Image& ResourceHolder::getImage(std::string const& filename, std::string const& id)
{
    if (id != "")
    {
        assert(mImages[id].loadFromFile(filename));
        return mImages.at(id);
    }
    else if (mImages.find(filename) == mImages.end())
    {
        assert(mImages[filename].loadFromFile(filename));
    }
    return mImages.at(filename);
}

sf::Texture& ResourceHolder::getTexture(std::string const& filename, std::string const& id)
{
    if (id != "")
    {
        assert(mTextures[id].loadFromFile(filename));
        return mTextures.at(id);
    }
    else if (mTextures.find(filename) == mTextures.end())
    {
        assert(mTextures[filename].loadFromFile(filename));
    }
    return mTextures.at(filename);
}

} // namespace ah
