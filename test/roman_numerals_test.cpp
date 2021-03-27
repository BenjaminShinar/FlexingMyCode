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

bool VerifyConvertFromNumberToString(unsigned int number, const std::string & expected)
{   
    std::string rep= RomanNumeral::MakeText(number);
    auto res{expected.compare(rep) == 0};
    std::cout <<std::boolalpha << "string representation of " << number  << " is " << rep << ". as expected? " << res << '\n';
    return res;
}
void TestConversionNumberToText()
{
    VerifyConvertFromNumberToString(1,"I");
    VerifyConvertFromNumberToString(2,"II");
    VerifyConvertFromNumberToString(3,"III");
    VerifyConvertFromNumberToString(4,"IV");
    VerifyConvertFromNumberToString(5,"V");
    VerifyConvertFromNumberToString(6,"VI");
    VerifyConvertFromNumberToString(7,"VII");
    VerifyConvertFromNumberToString(8,"VIII");
    VerifyConvertFromNumberToString(9,"IX");
    VerifyConvertFromNumberToString(10,"X");
    VerifyConvertFromNumberToString(14,"XIV");
    VerifyConvertFromNumberToString(34,"XXXIV");
    VerifyConvertFromNumberToString(35,"XXXV");
    VerifyConvertFromNumberToString(36,"XXXVI");
    VerifyConvertFromNumberToString(49,"IL"); //non standard cnversion
    VerifyConvertFromNumberToString(50,"L");
    VerifyConvertFromNumberToString(51,"LI");
    VerifyConvertFromNumberToString(98,"XCVIII");
    VerifyConvertFromNumberToString(99,"IC"); //non standard cnversion
    VerifyConvertFromNumberToString(100,"C");
    VerifyConvertFromNumberToString(499,"ID");//non standard cnversion
    VerifyConvertFromNumberToString(499,"CDXCIX");
    VerifyConvertFromNumberToString(500,"D");
    VerifyConvertFromNumberToString(506,"DVI");
    VerifyConvertFromNumberToString(777,"DCCLXXVII");
    VerifyConvertFromNumberToString(999,"IM");//non standard cnversion
    VerifyConvertFromNumberToString(1000,"M");
    VerifyConvertFromNumberToString(2222,"MMCCXXII");
    

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

int main()
{

IsStringValid("XII");
IsStringValid("Xi");
IsStringValid("Xe");
GetAmountsValueSimple({.I_Count=5},5);
GetAmountsValueSimple({.I_Count=3},5);
GetAmountsValueSimple({.X_Count=1},10);
GetAmountsValueSimple({.I_Count=1,.V_Count=1,.L_Count=1},56);
TestConversionNumberToText();
return 0;
}