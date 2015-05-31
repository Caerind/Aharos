#ifndef AH_DATAMANAGER_HPP
#define AH_DATAMANAGER_HPP

#include <map>
#include <string>

#include "String.hpp"

namespace ah
{

class DataManager
{
    public:
        DataManager();

        template<typename T>
        void setData(std::string const& id, T const& data);

        template<typename T>
        T getData(std::string const& id);

    private:
        std::map<std::string,std::string> mData;
};

template<typename T>
void DataManager::setData(std::string const& id, T const& data)
{
    mData[id] = to_string<T>(data);
}

template<typename T>
T DataManager::getData(std::string const& id)
{
    if (mData.find(id) != mData.end())
        return from_string<T>(mData[id]);
    return T();
}

}

#endif // AH_DATAMANAGER_HPP
