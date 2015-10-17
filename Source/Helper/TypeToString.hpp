#ifndef LP_TYPETOSTRING_HPP_INCLUDED
#define LP_TYPETOSTRING_HPP_INCLUDED

// Code found here : http://www.cplusplus.com/forum/beginner/100627/
// Thanks to http://www.cplusplus.com/user/JLBorges/ for this

#include <iostream>
#include <string>
#include <typeinfo>

#ifdef __GNUG__ // GCC

#include <cxxabi.h>
#include <cstdlib>

namespace lp
{

static std::string readable_name( const char* mangled_name )
{
    int status ;
    char* temp = __cxxabiv1::__cxa_demangle( mangled_name, nullptr, nullptr, &status ) ;
    if(temp)
    {
        std::string result(temp) ;
        std::free(temp) ;
        return result ;
    }
    else return mangled_name ;
}

} // namespace lp

#else // not GCC

namespace lp
{

std::string readable_name( const char* mangled_name ) { return mangled_name ; }

} // namespace lp

#endif // __GNUG__

namespace lp
{

template < typename T > std::string type()
{ return readable_name( typeid(T).name() ) ; }

template < typename T > std::string type( const T& obj )
{ return readable_name( typeid(obj).name() ) ; }

} // namespace lp

#endif // LP_TYPETOSTRING_HPP_INCLUDED
