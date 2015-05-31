#include "SoundManager.hpp"

namespace ah
{

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
    mSounds.clear();
}

std::shared_ptr<sf::Sound> SoundManager::prepareSound(std::string const& filename)
{
    SoundManager::updateSoundManager();
    mSounds.push_back(std::make_shared<sf::Sound>());
    mSounds.back()->setBuffer(mSoundBuffers.acquire(filename,thor::Resources::fromFile<sf::SoundBuffer>(filename),thor::Resources::Reuse));
    return mSounds.back();
}

bool SoundManager::playSound(std::string const& filename)
{
    auto s = prepareSound(filename);
    if (s != nullptr)
    {
        s->play();
        return true;
    }
    return false;
}

void SoundManager::updateSoundManager()
{
    for (auto itr = mSounds.begin(); itr != mSounds.end(); itr++)
    {
        if ((*itr)->getStatus() == sf::Sound::Status::Stopped)
        {
            (*itr) = nullptr;
            mSounds.erase(itr);
        }
    }
}

}
