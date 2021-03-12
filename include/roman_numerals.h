#pragma once
#ifndef _ROMAN_NUMERLS_H__
#define _ROMAN_NUMERLS_H__

#include <string>
#include <string_view>
#include <map>
class RomanNumeral
{
    public:
    RomanNumeral(const std::string_view & str) : Roman(str),Number(TransfromToNumber(str)) {}
    static bool VerifyString(const std::string & str);
    //static constexpr std::string Transfrom(unsigned int num) { return "X";}
    static  unsigned int TransfromToNumber(const std::string_view & str) { return 5;}
    const std::string Roman;
    const unsigned int Number;


    struct Amounts
    {
        int Calculate() const 
        {
            const int  I_Value =  I_Count * RomanNumeral::CharactersWorth.at('I');
            const int  V_Value =  V_Count * RomanNumeral::CharactersWorth.at('V');
            const int  X_Value =  X_Count * RomanNumeral::CharactersWorth.at('X');
            const int  L_Value =  L_Count * RomanNumeral::CharactersWorth.at('L');
            const int  C_Value =  C_Count * RomanNumeral::CharactersWorth.at('C');
            const int  D_Value =  D_Count * RomanNumeral::CharactersWorth.at('D');
            const int  M_Value =  M_Count * RomanNumeral::CharactersWorth.at('M');

            return (I_Value + V_Value + X_Value + L_Value + C_Value + D_Value + M_Value );
        }
        
        int I_Count {0};
        int V_Count {0};
        int X_Count {0};
        int L_Count {0};
        int C_Count {0};
        int D_Count {0};
        int M_Count {0};
    };

    private:

    static constexpr auto AllowedCharacters ="IiVvXxLlCcDdMm";
    static std::map<char, int> CharactersWorth;
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