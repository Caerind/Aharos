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
        bool loadSoundBuffer(std::string const& id, Args&& ... args);
        template<typename ... Args>
        bool loadFont(std::string const& id, Args&& ... args);
        template<typename ... Args>
        bool loadImage(std::string const& id, Args&& ... args);
        template<typename ... Args>
        bool loadTexture(std::string const& id, Args&& ... args);
        template<typename ... Args>
        bool loadShader(std::string const& id, Args&& ... args);

        sf::SoundBuffer& getSoundBuffer(std::string const& id);
        sf::Font& getFont(std::string const& id);
        sf::Image& getImage(std::string const& id);
        sf::Texture& getTexture(std::string const& id);
        sf::Shader& getShader(std::string const& id);

        bool isSoundBufferLoaded(std::string const& id) const;
        bool isFontLoaded(std::string const& id) const;
        bool isImageLoaded(std::string const& id) const;
        bool isTextureLoaded(std::string const& id) const;
        bool isShaderLoaded(std::string const& id) const;

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
bool ResourceHolder::loadSoundBuffer(std::string const& id, Args&& ... args)
{
    bool res = mSoundBuffers[id].loadFromFile(std::forward<Args>(args)...);
    assert(res);
    return res;
}

template<typename ... Args>
bool ResourceHolder::loadFont(std::string const& id, Args&& ... args)
{
    bool res = mFonts[id].loadFromFile(std::forward<Args>(args)...);
    assert(res);
    return res;
}

template<typename ... Args>
bool ResourceHolder::loadImage(std::string const& id, Args&& ... args)
{
    bool res = mImages[id].loadFromFile(std::forward<Args>(args)...);
    assert(res);
    return res;
}

template<typename ... Args>
bool ResourceHolder::loadTexture(std::string const& id, Args&& ... args)
{
    bool res = mTextures[id].loadFromFile(std::forward<Args>(args)...);
    assert(res);
    return res;
}

template<typename ... Args>
bool ResourceHolder::loadShader(std::string const& id, Args&& ... args)
{
    bool res = mShaders[id].loadFromFile(std::forward<Args>(args)...);
    assert(res);
    return res;
}

} // namespace ah

#endif // AH_RESOURCEHOLDER_HPP
