#include "AudioListenerComponent.hpp"
#include "../Entity.hpp"

namespace ses
{

AudioListenerComponent::AudioListenerComponent()
{
    sf::Listener::setUpVector(0.f,1.f,0.f);
}

void AudioListenerComponent::update()
{
    if (mEntity != nullptr)
    {
        sf::Listener::setPosition(mEntity->getPosition().x,0.f,mEntity->getPosition().y);
    }
}

} // namespace ses
