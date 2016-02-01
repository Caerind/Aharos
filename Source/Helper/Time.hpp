#ifndef LP_TIME_HPP
#define LP_TIME_HPP

#include <ctime>
#include <string>

namespace lp
{

std::string getTime(std::string const& timeFormat);

int getHours();
int getMinutes();
int getSeconds();

int getDay();
int getMonth();
int getYear();

} // namespace lp

#endif // LP_TIME_HPP
