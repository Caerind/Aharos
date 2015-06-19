#ifndef AH_RESOURCEHOLDER_HPP
#define AH_RESOURCEHOLDER_HPP

#include <cassert>
#include <map>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace ah
{

class ResourceHolder
{
    public:
        ResourceHolder();

        template<typename ... Args>
        void loadSoundBuffer(std::string const& id, Args&& ... args);
        template<typename ... Args>
        void loadFont(std::string const& id, Args&& ... args);
        template<typename ... Args>
        void loadImage(std::string const& id, Args&& ... args);
        template<typename ... Args>
        void loadTexture(std::string const& id, Args&& ... args);
        template<typename ... Args>
        void loadShader(std::string const& id, Args&& ... args);

        sf::SoundBuffer& getSoundBuffer(std::string const& id);
        sf::Font& getFont(std::string const& id);
        sf::Image& getImage(std::string const& id);
        sf::Texture& getTexture(std::string const& id);
        sf::Shader& getShader(std::string const& id);

        void releaseSoundBuffer(std::string const& id);
        void releaseFont(std::string const& id);
        void releaseImage(std::string const& id);
        void releaseTexture(std::string const& id);
        void releaseShader(std::string const& id);

    private:
        std::map<std::string,sf::SoundBuffer> mSoundBuffers;
        std::map<std::string,sf::Font> mFonts;
        std::map<std::string,sf::Image> mImages;
        std::map<std::string,sf::Texture> mTextures;
        std::map<std::string,sf::Shader> mShaders;
};

template<typename ... Args>
void ResourceHolder::loadSoundBuffer(std::string const& id, Args&& ... args)
{
    assert(mSoundBuffers[id].loadFromFile(std::forward<Args>(args)...));
}

template<typename ... Args>
void ResourceHolder::loadFont(std::string const& id, Args&& ... args)
{
    assert(mFonts[id].loadFromFile(std::forward<Args>(args)...));
}

template<typename ... Args>
void ResourceHolder::loadImage(std::string const& id, Args&& ... args)
{
    assert(mImages[id].loadFromFile(std::forward<Args>(args)...));
}

template<typename ... Args>
void ResourceHolder::loadTexture(std::string const& id, Args&& ... args)
{
    assert(mTextures[id].loadFromFile(std::forward<Args>(args)...));
}

template<typename ... Args>
void ResourceHolder::loadShader(std::string const& id, Args&& ... args)
{
    assert(mShaders[id].loadFromFile(std::forward<Args>(args)...));
}

} // namespace ah

#endif // AH_RESOURCEHOLDER_HPP
