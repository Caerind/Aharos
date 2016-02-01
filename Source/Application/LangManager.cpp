#include "LangManager.hpp"

namespace ah
{

LangManager::LangManager()
{
    load();
}

bool LangManager::setLang(std::string const& lang)
{
    if (mLangs.find(lang) != mLangs.end())
    {
        mActualLang = lang;
        return true;
    }
    else
    {
        mActualLang = "";
        return false;
    }
}

std::string LangManager::getLang() const
{
    return mActualLang;
}

std::vector<std::string> LangManager::getLoadedLangs()
{
    std::vector<std::string> langs;
    for (auto itr = mLangs.begin(); itr != mLangs.end(); itr++)
    {
        langs.push_back(itr->first);
    }
    return langs;
}

void LangManager::set(std::string const& id, std::string const& str)
{
    if (mActualLang != "")
    {
        if (mLangs.at(mActualLang).find(id) != mLangs.at(mActualLang).end())
        {
            mLangs.at(mActualLang)[id] = str;
        }
    }
}

std::string LangManager::get(std::string const& id) const
{
    if (mActualLang != "")
    {
        if (mLangs.at(mActualLang).find(id) != mLangs.at(mActualLang).end())
        {
            return mLangs.at(mActualLang).at(id);
        }
    }
    return id;
}

bool LangManager::load()
{
    DIR* dir = nullptr;
    struct dirent* file = nullptr;
    dir = opendir("Assets/Lang");
    if (dir == nullptr)
    {
        return false;
    }

    while ((file = readdir(dir)) != nullptr)
    {
        std::string n = file->d_name;
        if (n.find(".lang") != std::string::npos)
        {
            std::ifstream file("Assets/Lang/" + n);
            if (file)
            {
                std::string langName;
                std::getline(file,langName);
                std::string line;
                while (std::getline(file,line))
                {
                    auto f = line.find("=");
                    std::string id = line.substr(0,f);
                    std::string str = line.substr(f+1);
                    mLangs[langName][id] = str;
                }
            }
        }
    }

    return true;
}

} // namespace ah
