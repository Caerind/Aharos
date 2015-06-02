#ifndef AH_LANG_HPP
#define AH_LANG_HPP

#include <fstream>
#include <map>
#include <string>

namespace ah
{

class Lang
{
    public:
        Lang();

        std::string getLang(std::string const& id);

        void loadLang(std::string const& filename);

    private:
        std::map<std::string,std::string> mLang;
};

}

#endif // AH_LANG_HPP
