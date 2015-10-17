#ifndef ES_TYPETOSTRING_HPP_INCLUDED
#define ES_TYPETOSTRING_HPP_INCLUDED

// Code found here : http://www.cplusplus.com/forum/beginner/100627/
// Thanks to http://www.cplusplus.com/user/JLBorges/ for this

#include <iostream>
#include <string>
#include <typeinfo>

#ifdef __GNUG__ // GCC

#include <cxxabi.h>
#include <cstdlib>

namespace es
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

} // namespace es

#else // not GCC

namespace es
{

std::string readable_name( const char* mangled_name ) { return mangled_name ; }

} // namespace es

#endif // __GNUG__

namespace es
{

template < typename T > std::string type_to_string()
{ return readable_name( typeid(T).name() ) ; }

template < typename T > std::string type_to_string( const T& obj )
{ return readable_name( typeid(obj).name() ) ; }

} // namespace es

#endif // ES_TYPETOSTRING_HPP_INCLUDED
