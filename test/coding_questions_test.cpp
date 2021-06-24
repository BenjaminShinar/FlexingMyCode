#include "../include/coding_questions.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <time.h>
int main()
{
    srand(time(0));

    unsigned int millionChars[1'000'00]{0};
    const auto elements = sizeof(millionChars) / sizeof(unsigned int);
    std::size_t slow{1}, regular{1}, fast{1000000000};
    const auto requiredMatch{100};
    std::vector<unsigned int> targets(requiredMatch);
    for (auto i = 0u; i < elements; ++i)
    {
        millionChars[i] = (rand() % 10000);
    }
    std::generate(std::begin(targets), std::end(targets), []()
                  { return (rand() % 10000); });

    std::cout << "total elemnts in array " << elements << '\n';
    {
        TimerWithExportedValue t(&slow, "slow");
        for (auto target : targets)
        {
            auto match = SlowFindInArray(millionChars, elements, target);
        }
    }
    {
        TimerWithExportedValue t(&regular, "regular");
        for (auto target : targets)
        {
            auto match = FindInArray(millionChars, elements, target);
        }
    }
    {
        TimerWithExportedValue t(&fast, "fast");
        for (auto target : targets)
        {
            auto match = BetterFindInArray(millionChars, elements, target);
        }
    }
    std::cout << "slow " << slow << " is slower than regular " << regular << "? " << (slow > regular) << '\n';
    std::cout << "regular " << regular << " is slower than fast " << fast << "? " << (regular > fast) << '\n';
}