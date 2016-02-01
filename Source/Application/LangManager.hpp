#ifndef AH_LANGMANAGER_HPP
#define AH_LANGMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

namespace ah
{

class LangManager
{
    public:
        LangManager();

        bool setLang(std::string const& lang);
        std::string getLang() const;
        std::vector<std::string> getLoadedLangs();

        void set(std::string const& id, std::string const& str);
        std::string get(std::string const& id) const;

        bool load();

    protected:
        std::string mActualLang;
        std::map<std::string,std::map<std::string,std::string>> mLangs;
};

} // namespace ah

#endif // AH_LANGMANAGER_HPP
