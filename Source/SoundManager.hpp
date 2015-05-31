#ifndef AH_SOUNDMANAGER_HPP
#define AH_SOUNDMANAGER_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <Thor/Resources.hpp>

namespace ah
{

class SoundManager
{
    public:
        SoundManager();
        ~SoundManager();

        std::shared_ptr<sf::Sound> prepareSound(std::string const& filename);
        bool playSound(std::string const& filename);

    private:
        void updateSoundManager();

    private:
        thor::ResourceHolder<sf::SoundBuffer,std::string> mSoundBuffers;
        std::vector<std::shared_ptr<sf::Sound>> mSounds;
};

}

#endif // AH_SOUNDMANAGER_HPP
