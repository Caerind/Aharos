#include "Time.hpp"

namespace lp
{

std::string getTime(std::string const& timeFormat)
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,timeFormat.c_str(),timeinfo);
    return std::string(buffer);
}

int getHours()
{
    return std::stoi(getTime("%H"));
}

int getMinutes()
{
    return std::stoi(getTime("%M"));
}

int getSeconds()
{
    return std::stoi(getTime("%S"));
}

int getDay()
{
    return std::stoi(getTime("%d"));
}

int getMonth()
{
    return std::stoi(getTime("%m"));
}

int getYear()
{
    return std::stoi(getTime("%y"));
}

} // namespace lp
