#include "ResourceManager.hpp"

namespace ah
{

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::load()
{
    pugi::xml_document doc;
    if (!doc.load_file("Assets/Data/settings.xml"))
    {
        return false;
    }
    pugi::xml_node resources = doc.child("Resources");
    if (!resources)
    {
        return false;
    }
    for (pugi::xml_node res : resources.children("Resource"))
    {
        std::string type = res.attribute("type").value();
        std::string id = res.attribute("id").value();
        std::string file = res.attribute("file").value();

        if (type == "sf::Texture")
        {
            loadTexture(id,file);
        }
        else if (type == "sf::Image")
        {
            loadImage(id,file);
        }
        else if (type == "sf::Font")
        {
            loadFont(id,file);
        }
        else if (type == "sf::SoundBuffer")
        {
            loadSoundBuffer(id,file);
        }
    }
    return true;
}

void ResourceManager::save()
{
    pugi::xml_document doc;
    doc.load_file("Assets/Data/settings.xml");
    if (doc.child("Resources"))
    {
        doc.remove_child("Resources");
    }
    pugi::xml_node res = doc.append_child("Resources");
    for (std::size_t i = 0; i < mResources.size(); i++)
    {
        pugi::xml_node r = res.append_child("Resource");
        r.append_attribute("type") = mResources[i].type.c_str();
        r.append_attribute("id") = mResources[i].id.c_str();
        r.append_attribute("file") = mResources[i].filename.c_str();
    }
    doc.save_file("Assets/Data/settings.xml");
}

void ResourceManager::loadTexture(std::string const& id, std::string const& filename)
{
    mResources.push_back(mTextures.load(id,filename));
}

void ResourceManager::loadImage(std::string const& id, std::string const& filename)
{
    mResources.push_back(mImages.load(id,filename));
}

void ResourceManager::loadFont(std::string const& id, std::string const& filename)
{
    mResources.push_back(mFonts.load(id,filename));
}

void ResourceManager::loadSoundBuffer(std::string const& id, std::string const& filename)
{
    mResources.push_back(mSoundBuffers.load(id,filename));
}

bool ResourceManager::isLoadedTexture(std::string const& id) const
{
    return mTextures.isLoaded(id);
}

bool ResourceManager::isLoadedImage(std::string const& id) const
{
    return mImages.isLoaded(id);
}

bool ResourceManager::isLoadedFont(std::string const& id) const
{
    return mFonts.isLoaded(id);
}

bool ResourceManager::isLoadedSoundBuffer(std::string const& id) const
{
    return mSoundBuffers.isLoaded(id);
}

sf::Texture& ResourceManager::getTexture(std::string const& id, std::string const& filename)
{
    return mTextures.get(id,filename);
}

sf::Image& ResourceManager::getImage(std::string const& id, std::string const& filename)
{
    return mImages.get(id,filename);
}

sf::Font& ResourceManager::getFont(std::string const& id, std::string const& filename)
{
    return mFonts.get(id,filename);
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string const& id, std::string const& filename)
{
    return mSoundBuffers.get(id,filename);
}

void ResourceManager::releaseTexture(std::string const& id)
{
    if (mTextures.release(id))
    {
        removeResource(id);
    }
}

void ResourceManager::releaseImage(std::string const& id)
{
    if (mImages.release(id))
    {
        removeResource(id);
    }
}

void ResourceManager::releaseFont(std::string const& id)
{
    if (mFonts.release(id))
    {
        removeResource(id);
    }
}

void ResourceManager::releaseSoundBuffer(std::string const& id)
{
    if (mSoundBuffers.release(id))
    {
        removeResource(id);
    }
}

void ResourceManager::removeResource(std::string const& id)
{
    for (std::size_t i = 0; i < mResources.size(); i++)
    {
        if (mResources[i].id == id)
        {
            mResources.erase(i + mResources.begin());
        }
    }
}



} // namespace ah
