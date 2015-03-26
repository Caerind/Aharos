#include "MusicManager.hpp"

MusicManager MusicManager::gInstance;
bool MusicManager::gInitialised;

MusicManager* MusicManager::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

std::shared_ptr<sf::Music> MusicManager::playLoop(std::string const& filename)
{
    if (instance() != nullptr)
    {
        instance()->mMusic->setLoop(true);
        if (instance()->mMusic->openFromFile(filename))
        {
            instance()->mMusic->play();
        }
        return instance()->mMusic;
    }
    return nullptr;
}

std::shared_ptr<sf::Music> MusicManager::playList()
{
    if (instance() != nullptr)
    {
        instance()->mMusic->setLoop(false);
        MusicManager::update();
        return instance()->mMusic;
    }
    return nullptr;
}

std::vector<std::string>* MusicManager::getPlaylist()
{
    if (instance() != nullptr)
    {
        return &instance()->mFilenames;
    }
    return nullptr;
}

void MusicManager::update()
{
    if (instance() != nullptr)
    {
        if (!instance()->mMusic->getLoop() && instance()->mMusic->getStatus() == sf::Music::Status::Stopped)
        {
            // TODO : Replace 0 by random func
            if (instance()->mMusic->openFromFile(instance()->mFilenames.at(0)))
            {
                instance()->mMusic->play();
            }
        }
    }
}

MusicManager::MusicManager()
{
    gInitialised = true;
    mMusic = std::make_shared<sf::Music>();
    mMusic->setLoop(true);
}

MusicManager::~MusicManager()
{
    mMusic = nullptr;
    gInitialised = false;
}
