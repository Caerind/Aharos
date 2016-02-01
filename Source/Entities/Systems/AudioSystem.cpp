#include "AudioSystem.hpp"
#include "../World.hpp"

namespace ses
{

AudioSystem::AudioSystem()
{
    mEntities.requiresOne({lp::type<AudioListenerComponent>(),lp::type<AudioSourceComponent>()});
}

void AudioSystem::playMusic(std::string const& entityId, std::string const& musicId, bool loop)
{
    if (mEntities.contains(entityId))
    {
        Entity::Ptr e = mEntities.get(entityId);
        if (e != nullptr)
        {
            if (e->hasComponent<AudioSourceComponent>())
            {
                e->getComponent<AudioSourceComponent>().playMusic(musicId,loop);
            }
        }
    }
}

void AudioSystem::playSound(std::string const& entityId, std::string const& soundId, bool loop)
{
    if (mEntities.contains(entityId))
    {
        Entity::Ptr e = mEntities.get(entityId);
        if (e != nullptr)
        {
            if (e->hasComponent<AudioSourceComponent>())
            {
                e->getComponent<AudioSourceComponent>().playSound(soundId,loop);
            }
        }
    }
}

void AudioSystem::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntities.at(i) != nullptr)
        {
            if (mEntities.at(i)->hasComponent<AudioListenerComponent>())
            {
                mEntities.at(i)->getComponent<AudioListenerComponent>().update();
            }
            if (mEntities.at(i)->hasComponent<AudioSourceComponent>())
            {
                mEntities.at(i)->getComponent<AudioSourceComponent>().update();
            }
        }
    }
}

void AudioSystem::handleMessage(sf::Packet& packet)
{
    // TODO : Handle Audio Packets
}

} // namespace ses
