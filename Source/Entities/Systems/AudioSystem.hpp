#ifndef SES_AUDIOSYSTEM_HPP
#define SES_AUDIOSYSTEM_HPP

#include "../System.hpp"
#include "../Components.hpp"

namespace ses
{

class AudioSystem : public System
{
    public:
        AudioSystem();

        void playMusic(std::string const& entityId, std::string const& musicId, bool loop);
        void playSound(std::string const& entityId, std::string const& soundId, bool loop = false);

        void update();

        void handleMessage(sf::Packet& packet);
};

} // namespace ses

#endif // SES_AUDIOSYSTEM_HPP
