#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ctime>
#include <string>

#include "String.hpp"

std::string getTime(std::string timeFormat);

int getHours();
int getMinutes();
int getSeconds();

int getDay();
int getMonth();
int getYear();

#endif // CLOCK_HPP
