#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <vector>
#include <memory>
#include <string>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceHolder.hpp"

class SoundManager
{
    public:
        static SoundManager* instance();

        static std::shared_ptr<sf::Sound> prepare(std::string const& filename);
        static bool play(std::string const& filename);

        static void update();

    private:
        SoundManager();
        ~SoundManager();

        static SoundManager gInstance;
        static bool gInitialised;

        std::vector<std::shared_ptr<sf::Sound>> mSounds;
};

#endif // SOUNDMANAGER_HPP
