#include "../include/roman_numerals.h"
#include <cmath>
#include <vector>
#include <deque>
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


char GetNextSymbol(char c)
{
    switch (c)
    {
    case 'I': return 'X'; break;
    case 'X': return 'C'; break;
    case 'C': return 'M'; break;
    case 'M': return 'Z'; break;
    }
    return '0';
}

char GetPreviousSymbol(char c)
{
    switch (c)
    {
    case 'X': return 'I'; break;
    case 'C': return 'X'; break;
    case 'M': return 'C'; break;
    case 'Z': return 'M'; break;
    }
    return '0';
}

char GetStartingSymbol(int number)
{
    if (number < 10)
        return 'I';
    else if (number <100)
        return 'X';
    else if (number <1000)
        return 'C';
    else if (number <10000)
        return 'M';
    return 'Z';
}

bool RomanNumeral::VerifyString(const std::string & str)
{
    auto z = str.find_first_not_of(AllowedCharacters);
    return z == std::string::npos;
}
std::deque<int> GetDigits(int n)
{
    std::deque<int> digits;
    if(n == 0)
    {
        digits.push_front(0);
    }

    n = abs(n);
    while(n > 0)
    {
        digits.push_front( n % 10);
        n = n /10;
    }
    return digits;

}
std::string RomanNumeral::MakeText(const unsigned int number)
{
    int easier = static_cast<int>(number);
    auto firstSymbol =  GetStartingSymbol(number);
    auto digits = GetDigits(easier);

    return DecomposeDeque(digits,firstSymbol);
    //0 - do nothing
    //[0,1,2,3] - return [1,2,3] times the symbol
    // [4] return the symbol once and the 'middle' symbol
    // [5] return the middle symbol
    // [6,7,8] return the middle symbol and the [1,2,3] times the symbol
    // [9] return the symbol once and the 'big' symbol

}

std::string RomanNumeral::DecomposeDeque(std::deque<int>  & digits, char symbol)
{
    if (digits.empty())
    return "";
    auto current = MakeTextRec(digits.front(),symbol);
    digits.pop_front();
    return current + DecomposeDeque(digits,GetPreviousSymbol(symbol));
}
char GetMiddleSymbol(char c)
{
    switch (c)
    {
    case 'I': return 'V'; break;
    case 'X': return 'L'; break;
    case 'C': return 'D'; break;
    case 'M': return 'W'; break;
    }
    return '0';
}

std::string RomanNumeral::MakeTextRec(int number, char symbol)
{

    switch (number)
    {
    case 0:
        return "";
        break;
    case 1: 
    case 2: 
    case 3: 
        return std::string(number,symbol);
        break;
    case 4: 
    case 5: 
    {
        auto str = MakeTextRec(5-number,symbol);
        auto mid = std::string(1,GetMiddleSymbol(symbol));
        return {str+ mid};
        break;
    }
    break;
    case 6: 
    case 7: 
    case 8: 
    {
        auto str = MakeTextRec(number-5,symbol);
        auto mid = std::string(1,GetMiddleSymbol(symbol));
        return {mid+str};
        break;
    }
    break;
    case 9:
    {
        auto str = MakeTextRec(10-number,symbol);
        auto big = std::string(1,GetNextSymbol(symbol));
        return {str+ big};
        break;
    }
    default:
        return "BAD";
        break;
    }
}

/*


*/