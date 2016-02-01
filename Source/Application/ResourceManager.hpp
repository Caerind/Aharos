#ifndef AH_RESOURCEMANAGER_HPP
#define AH_RESOURCEMANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <Thor/Resources.hpp>

#include "../Helper/pugixml.hpp"
#include "../Helper/TypeToString.hpp"

namespace ah
{

// TODO : ResourcePack
class ResourceManager
{
    public:
        ResourceManager();
        ~ResourceManager();

        bool load();
        void save();

        void loadTexture(std::string const& id, std::string const& filename);
        void loadImage(std::string const& id, std::string const& filename);
        void loadFont(std::string const& id, std::string const& filename);
        void loadSoundBuffer(std::string const& id, std::string const& filename);

        bool isLoadedTexture(std::string const& id) const;
        bool isLoadedImage(std::string const& id) const;
        bool isLoadedFont(std::string const& id) const;
        bool isLoadedSoundBuffer(std::string const& id) const;

        sf::Texture& getTexture(std::string const& id, std::string const& filename = "");
        sf::Image& getImage(std::string const& id, std::string const& filename = "");
        sf::Font& getFont(std::string const& id, std::string const& filename = "");
        sf::SoundBuffer& getSoundBuffer(std::string const& id, std::string const& filename = "");

        void releaseTexture(std::string const& id);
        void releaseImage(std::string const& id);
        void releaseFont(std::string const& id);
        void releaseSoundBuffer(std::string const& id);

    protected:
        struct Resource
        {
            std::string type;
            std::string id;
            std::string filename;
            bool loaded;
        };

        template <typename T>
        struct ResourceHolder
        {
            std::map<std::string,std::pair<Resource,T>> resources;
            Resource load(std::string const& id, std::string const& filename);
            bool isLoaded(std::string const& id) const;
            T& get(std::string const& id, std::string const& filename = "");
            bool release(std::string const& id);
        };

        void removeResource(std::string const& id);

    protected:
        std::vector<Resource> mResources;

        ResourceHolder<sf::Texture> mTextures;
        ResourceHolder<sf::Image> mImages;
        ResourceHolder<sf::Font> mFonts;
        ResourceHolder<sf::SoundBuffer> mSoundBuffers;
};

template <typename T>
ResourceManager::Resource ResourceManager::ResourceHolder<T>::load(std::string const& id, std::string const& filename)
{
    Resource r;
    r.type = lp::type<T>();
    r.id = id;
    r.filename = filename;
    resources[r.id].first = r;
    if (!resources[r.id].second.loadFromFile(filename))
    {
        resources[r.id].first.loaded = false;
        throw thor::ResourceLoadingException("Can't load " + filename);
    }
    else
    {
        resources[r.id].first.loaded = true;
    }
    return r;
}

template <typename T>
bool ResourceManager::ResourceHolder<T>::isLoaded(std::string const& id) const
{
    if (resources.find(id) == resources.end())
    {
        return false;
    }
    return resources.at(id).first.loaded;
}

template <typename T>
T& ResourceManager::ResourceHolder<T>::get(std::string const& id, std::string const& filename)
{
    if (filename != "")
    {
        load(id,filename);
    }
    for (auto itr = resources.begin(); itr != resources.end(); itr++)
    {
        if (itr->first == id)
        {
            return itr->second.second;
        }
    }
    assert(false && "File don't exists");
}

template <typename T>
bool ResourceManager::ResourceHolder<T>::release(std::string const& id)
{
    for (auto itr = resources.begin(); itr != resources.end(); itr++)
    {
        if (itr->first == id)
        {
            resources.erase(itr);
            return true;
        }
    }
    return false;
}

} // namespace ah

#endif // AH_RESOURCEMANAGER_HPP
