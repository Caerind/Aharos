#ifndef SES_AUDIOSOURCECOMPONENT_HPP
#define SES_AUDIOSOURCECOMPONENT_HPP

#include "../Component.hpp"
#include "../../Application/Application.hpp"

namespace ses
{

class AudioSourceComponent : public Component
{
    public:
        AudioSourceComponent();

        ah::AudioSource::Ptr playMusic(std::string const& id, bool loop);
        ah::AudioSource::Ptr playSound(std::string const& id, bool loop = false);
        void update();

    protected:
        std::vector<ah::AudioSource::Ptr> mSources;
};

} // namespace ses


#endif // SES_AUDIOSOURCECOMPONENT_HPP
