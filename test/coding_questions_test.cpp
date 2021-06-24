#include "../include/coding_questions.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <time.h>
int main()
{
    srand(time(0));

    unsigned int millionChars[1'00]{0};
    const auto elements = sizeof(millionChars) / sizeof(unsigned int);
    for (auto i = 0u; i < elements; ++i)
    {
        millionChars[i] = (rand() % 256);
    }
    std::vector<unsigned int> targets{(rand() % 256u), (rand() % 256u), (rand() % 256u)};

    std::cout << elements << '\n';
    for (auto target : targets)
    {
        std::cout << "traget " << target << " exists? " << FindInArray(millionChars, elements, target) << '\n';
    }
}