#include "ResourceHolder.hpp"

namespace ah
{

ResourceHolder::ResourceHolder()
{
}

sf::SoundBuffer& ResourceHolder::getSoundBuffer(std::string const& id)
{
    return mSoundBuffers.at(id);
}

sf::Font& ResourceHolder::getFont(std::string const& id)
{
    return mFonts.at(id);
}

sf::Image& ResourceHolder::getImage(std::string const& id)
{
    return mImages.at(id);
}

sf::Texture& ResourceHolder::getTexture(std::string const& id)
{
    return mTextures.at(id);
}

sf::Shader& ResourceHolder::getShader(std::string const& id)
{
    return mShaders.at(id);
}

void ResourceHolder::releaseSoundBuffer(std::string const& id)
{
    auto itr = mSoundBuffers.find(id);
    if (itr != mSoundBuffers.end())
    {
        mSoundBuffers.erase(itr);
    }
}

void ResourceHolder::releaseFont(std::string const& id)
{
    auto itr = mFonts.find(id);
    if (itr != mFonts.end())
    {
        mFonts.erase(itr);
    }
}

void ResourceHolder::releaseImage(std::string const& id)
{
    auto itr = mImages.find(id);
    if (itr != mImages.end())
    {
        mImages.erase(itr);
    }
}

void ResourceHolder::releaseTexture(std::string const& id)
{
    auto itr = mTextures.find(id);
    if (itr != mTextures.end())
    {
        mTextures.erase(itr);
    }
}

void ResourceHolder::releaseShader(std::string const& id)
{
    auto itr = mShaders.find(id);
    if (itr != mShaders.end())
    {
        mShaders.erase(itr);
    }
}

} // namespace ah
