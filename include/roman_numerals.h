#ifndef _ROMAN_NUMERLS_H__
#define _ROMAN_NUMERLS_H__

#include <string>
#include <string_view>
struct RomanNumeral
{
    RomanNumeral(const std::string_view & str) : Roman(str),Number(TransfromToNumber(str)) {}
    static bool VerifyString(const std::string_view & str);
    //static constexpr std::string Transfrom(unsigned int num) { return "X";}
    static  unsigned int TransfromToNumber(const std::string_view & str) { return 5;}
    const std::string Roman;
    const unsigned int Number;

    private:
    static constexpr auto AllowedCharacters ="IVXLCDM";
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
//constexpr ctor that takes compile time string
//ability to verify string is fit for this
//from unsigned number to string
//from string to class

#endif 
/*_ROMAN_NUMERLS_H__*/;