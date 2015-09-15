#ifndef AH_CLOCK_HPP
#define AH_CLOCK_HPP

#include <ctime>
#include <string>

#include "../Helper/String.hpp"

namespace ah
{

std::string getTime(std::string timeFormat);

int getHours();
int getMinutes();
int getSeconds();

int getDay();
int getMonth();
int getYear();

}

#endif // AH_CLOCK_HPP
