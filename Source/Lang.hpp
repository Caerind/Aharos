#ifndef LANG_HPP
#define LANG_HPP

#include <fstream>
#include <map>
#include <string>

class Lang
{
    public:
        Lang();

        std::string getLang(std::string const& id);

    protected:
        void loadLang(std::string const& filename);

    private:
        std::map<std::string,std::string> mLang;
};

#endif // LANG_HPP
