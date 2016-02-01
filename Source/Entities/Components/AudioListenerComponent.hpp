#ifndef SES_AUDIOLISTENERCOMPONENT_HPP
#define SES_AUDIOLISTENERCOMPONENT_HPP

#include <SFML/Audio/Listener.hpp>
#include "../Component.hpp"

namespace ses
{

class AudioListenerComponent : public Component
{
    public:
        AudioListenerComponent();

        void update();
};

} // namespace ses

#endif // SES_AUDIOLISTENERCOMPONENT_HPP
