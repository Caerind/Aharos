#ifndef STRING_HPP
#define STRING_HPP

#include <sstream>

template<typename T>
std::string to_string(T const& value);

template<typename T>
T from_string(std::string const& str);

template<typename T>
bool from_string(std::string const& str, T& dest);

template<typename T>
std::string to_string(T const& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template<typename T>
T from_string(std::string const& str)
{
    std::istringstream iss(str);
    T var;
    iss >> var;
    return var;
}

template<typename T>
bool from_string(std::string const& str, T& dest)
{
    std::istringstream iss(str);
    return iss >> dest != 0;
}

#endif // STRING_HPP
