#include "AudioSourceComponent.hpp"
#include "../Entity.hpp"

namespace ses
{

AudioSourceComponent::AudioSourceComponent()
{
}

ah::AudioSource::Ptr AudioSourceComponent::playMusic(std::string const& id, bool loop)
{
    if (mEntity != nullptr)
    {
        ah::AudioSource::Ptr m = ah::Application::getAudio().playMusic(id,loop,mEntity->getPosition());
        if (m != nullptr)
        {
            mSources.push_back(m);
        }
        return m;
    }
    return nullptr;
}

ah::AudioSource::Ptr AudioSourceComponent::playSound(std::string const& id, bool loop)
{
    if (mEntity != nullptr)
    {
        ah::AudioSource::Ptr s = ah::Application::getAudio().playSound(id,loop,mEntity->getPosition());
        if (s != nullptr)
        {
            mSources.push_back(s);
        }
        return s;
    }
    return nullptr;
}

void AudioSourceComponent::update()
{
    sf::Vector2f p;
    if (mEntity != nullptr)
    {
        p = mEntity->getPosition();
    }
    for (auto itr = mSources.begin(); itr != mSources.end(); itr++)
    {
        if ((*itr) != nullptr)
        {
            mSources.erase(itr);
        }
        else if (ah::Application::getAudio().getStatus() != sf::SoundSource::Stopped && (*itr)->getStatus() == sf::SoundSource::Stopped)
        {
            mSources.erase(itr);
        }
        else
        {
            (*itr)->setPosition(p);
        }
    }
}

} // namespace ses
