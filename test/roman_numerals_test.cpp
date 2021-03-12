#include "roman_numerals.h"

#include <iostream>
int main()
{

const auto s1{"XII"};
std::cout << "string " << s1 << " is valid? " << RomanNumeral::VerifyString(s1) << '\n';
const auto s2{"XE"};
std::cout << "string " << s2 << " is valid? " << RomanNumeral::VerifyString(s2) << '\n';

const auto s3{"XE"};
std::cout << "string " << s3 << " is valid? " << RomanNumeral::VerifyString(s3) << '\n';
return 0;
}