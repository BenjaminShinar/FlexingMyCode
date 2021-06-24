#include "../include/coding_questions.h"
#include <thread>
bool FindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x)
{
    const auto fin{arr + arr_size};

    for (auto ptr = arr; ptr < fin; ++ptr)
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

void BetterFindInArrayEarlyExit(const unsigned int *arr, std::size_t arr_size, unsigned int x, bool &continueSearcing)
{
    for (auto ptr = arr; (ptr < arr + arr_size) && continueSearcing; ++ptr)
    {
        if (*ptr == x)
        {
            continueSearcing = false;
            return;
        }
    }
    return;
}

bool BetterFindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x)
{
    bool contninueSearching{true};
    //BetterFindInArrayEarlyExit(arr, arr_size, x, contninueSearching);
    auto mid = arr_size / 2;
    std::thread t1(BetterFindInArrayEarlyExit, arr, mid, x, std::ref(contninueSearching));
    std::thread t2(BetterFindInArrayEarlyExit, arr + mid, arr_size - mid, x, std::ref(contninueSearching));
    t1.join();
    t2.join();
    return !contninueSearching;
}