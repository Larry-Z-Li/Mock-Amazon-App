#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<std::string> newSet;
    std::set<std::string>::iterator iter = s1.begin(); 	//Initializing iterator...
    for(int i = 0; i < s1.size(); i++)
    {
        if(s2.find(*iter)!= s2.end())
        {
            newSet.insert(*iter);
        }
        iter++;
    }
    return newSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<std::string> newSet;
    std::set<std::string>::iterator iter = s1.begin(); 	//Initializing iterator...
    for(int i = 0; i < s1.size(); i++)
    {
        newSet.insert(*iter);
        iter++;
    }

    iter = s2.begin();
    for(int i = 0; i < s2.size(); i++)
    {
        newSet.insert(*iter);
        iter++;
    }

    return newSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
