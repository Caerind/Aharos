#include "SoundManager.hpp"

SoundManager SoundManager::gInstance;
bool SoundManager::gInitialised;

SoundManager* SoundManager::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

std::shared_ptr<sf::Sound> SoundManager::prepare(std::string const& filename)
{
    SoundManager::update();
    if (instance() != nullptr)
    {
        instance()->mSounds.push_back(std::make_shared<sf::Sound>());
        auto b = ResourceHolder::get<sf::SoundBuffer>(filename);
        if (b != nullptr)
        {
            instance()->mSounds.back()->setBuffer(*b);
        }
        return instance()->mSounds.back();
    }
    return nullptr;
}

bool SoundManager::play(std::string const& filename)
{
    SoundManager::update();
    if (instance() != nullptr)
    {
        instance()->mSounds.push_back(std::make_shared<sf::Sound>());
        auto b = ResourceHolder::get<sf::SoundBuffer>(filename);
        if (b != nullptr)
        {
            instance()->mSounds.back()->setBuffer(*b);
            instance()->mSounds.back()->play();
            return true;
        }
    }
    return false;
}

void SoundManager::update()
{
    if (instance() != nullptr)
    {
        for (auto itr = instance()->mSounds.begin(); itr != instance()->mSounds.end(); itr++)
        {
            if ((*itr)->getStatus() == sf::Sound::Status::Stopped)
            {
                instance()->mSounds.erase(itr);
            }
        }
    }
}

SoundManager::SoundManager()
{
    gInitialised = true;
}

SoundManager::~SoundManager()
{
    mSounds.clear();
    gInitialised = false;
}
