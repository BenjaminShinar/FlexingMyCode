#include "../include/roman_numerals.h"

bool RomanNumeral::VerifyString(const std::string_view & str)
{
    auto z =str.find_first_not_of(AllowedCharacters,0);
    return z == -1;
}


/*
I 1
V 5
X 10
L 50
C 100
D 500
M 1000

*/