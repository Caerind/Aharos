#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <map>
#include <string>

#include <Thor/Graphics/ToString.hpp>

#include "String.hpp"

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
    T t;
    if (mData.find(id) != mData.end())
        if (!from_string(mData[id],t))
            return t;
    return T();
}




#endif // DATAMANAGER_HPP
