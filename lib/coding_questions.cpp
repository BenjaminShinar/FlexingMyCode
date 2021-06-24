#include "../include/coding_questions.h"

bool FindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x)
{
    for (auto ptr = arr; ptr < arr + arr_size; ++ptr)
    {
        if (*ptr == x)
        {
            return true;
        }
    }
    return false;
}

bool SlowFindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x)
{
    for (auto i = 0u; i < arr_size; ++i)
    {
        if (arr[i] == x)
        {
            return true;
        }
    }
    return false;
}

bool BetterFindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x)
{
    for (auto ptr = arr; ptr < arr + arr_size; ++ptr)
    {
        if (*ptr == x)
        {
            return true;
        }
    }
    return false;
}