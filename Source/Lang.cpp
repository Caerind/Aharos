#include "Lang.hpp"

namespace ah
{

Lang::Lang()
{
}

void Lang::loadLang(std::string const& filename)
{
    //mLang.clear(); // Do not clear the previous lang, if your new lang has missing words, you will use the old ones
    std::ifstream file(filename);
    if (file)
    {
        std::string line;
        while (std::getline(file,line))
        {
            if(!line.empty() && line[0] != '#')
            {
                size_t index = 0;
                const std::locale locale;
                while(std::isspace(line[index], locale))
                    index++;
                const int beginKeyString = index;
                while(!std::isspace(line[index], locale) && line[index] != '=')
                    index++;
                const std::string key = line.substr(beginKeyString, index - beginKeyString);
                while(std::isspace(line[index], locale) || line[index] == '=')
                    index++;
                if (!key.empty())
                {
                    mLang[key] = line.substr(index, line.size() - index);
                }
            }
        }
    }
}

std::string Lang::getLang(std::string const& id)
{
    if (mLang.find(id) != mLang.end())
    {
        return mLang.at(id);
    }
    return "";
}

}
