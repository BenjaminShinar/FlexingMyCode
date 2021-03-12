#include "../include/roman_numerals.h"

std::map<char,int> RomanNumeral::CharactersWorth =
{
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
};
bool RomanNumeral::VerifyString(const std::string & str)
{
    auto z = str.find_first_not_of(AllowedCharacters);
    return z == std::string::npos;
}


/*


*/