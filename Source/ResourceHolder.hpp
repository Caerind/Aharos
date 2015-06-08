#ifndef AH_RESOURCEHOLDER_HPP
#define AH_RESOURCEHOLDER_HPP

#include <cassert>
#include <map>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ah
{

class ResourceHolder
{
    public:
        ResourceHolder();

        sf::SoundBuffer&    getSoundBuffer(std::string const& filename, std::string const& id = "");
        sf::Font&           getFont(std::string const& filename, std::string const& id = "");
        sf::Image&          getImage(std::string const& filename, std::string const& id = "");
        sf::Texture&        getTexture(std::string const& filename, std::string const& id = "");

    private:
        std::map<std::string,sf::SoundBuffer> mSoundBuffers;
        std::map<std::string,sf::Font> mFonts;
        std::map<std::string,sf::Image> mImages;
        std::map<std::string,sf::Texture> mTextures;
};

}

#endif // AH_RESOURCEHOLDER_HPP
