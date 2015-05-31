#include "Clock.hpp"

namespace ah
{

std::string getTime(std::string timeFormat)
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,timeFormat.c_str(),timeinfo);
    return std::string(buffer);
}

int getHours()
{
    return from_string<int>(getTime("%H"));
}

int getMinutes()
{
    return from_string<int>(getTime("%M"));
}

int getSeconds()
{
    return from_string<int>(getTime("%S"));
}

int getDay()
{
    return from_string<int>(getTime("%d"));
}

int getMonth()
{
    return from_string<int>(getTime("%m"));
}

int getYear()
{
    return from_string<int>(getTime("%y"));
}

}
