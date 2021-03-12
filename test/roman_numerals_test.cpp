#include "roman_numerals.h"
#include <iostream>



bool IsStringValid(const std::string & str)
{
    auto b = RomanNumeral::VerifyString(str);
    std::cout <<std::boolalpha<< "string " << str << " is valid? " << b << '\n';
    return b;
}

bool GetAmountsValueSimple(const RomanNumeral::Amounts & amounts, int expected)
{
    auto val = amounts.Calculate();
    auto res{val == expected};
    std::cout <<std::boolalpha<< "amount is " << val << ". as expected? " << res << '\n';
    return res;
}
int main()
{

IsStringValid("XII");
IsStringValid("Xi");
IsStringValid("Xe");
GetAmountsValueSimple({.I_Count=5},5);
GetAmountsValueSimple({.I_Count=3},5);
GetAmountsValueSimple({.X_Count=1},10);
return 0;
}