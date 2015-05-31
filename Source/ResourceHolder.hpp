#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Thor/Resources.hpp>

class ResourceHolder
{
    public:
        ResourceHolder();

        sf::SoundBuffer&    getSoundBuffer(std::string const& filename);
        sf::Font&           getFont(std::string const& filename);
        sf::Image&          getImage(std::string const& filename);
        sf::Texture&        getTexture(std::string const& filename);

    private:
        thor::ResourceHolder<sf::SoundBuffer,   std::string> mSoundBuffers;
        thor::ResourceHolder<sf::Font,          std::string> mFonts;
        thor::ResourceHolder<sf::Image,         std::string> mImages;
        thor::ResourceHolder<sf::Texture,       std::string> mTextures;
};

#endif // RESOURCEHOLDER_HPP
