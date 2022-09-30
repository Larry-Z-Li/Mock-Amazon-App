#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords = trim(rawWords);
    std::set<std::string> strings;
    std::string temp;
    while(!rawWords.empty())															    //Loops by checking if the first character is a space or punctuation.
                                                                                        // If so, remove the character and add the temporary string into the set.
    {
        if(ispunct(rawWords[0]) || rawWords[0] == ' ')
        {
            if(temp.size() > 1)															//Keywords must be bigger than size 1
            {
                strings.insert(temp);
            }
            else
            {
                temp.clear();
            }
            temp = "";
            rawWords.erase(0,1);
        }
        else																							//If not, add the character into the temporary string for storage.
        {
            temp+=rawWords[0];
            rawWords.erase(0,1);
        }
    }
    if (temp.size() > 1)
    {
        strings.insert(temp);
    }
    return strings;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
            std::find_if(s.rbegin(),
                         s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
