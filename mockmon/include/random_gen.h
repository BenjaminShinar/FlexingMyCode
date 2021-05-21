#pragma once

#include <random>
#include <initializer_list>

namespace mockmon::random
{
   
    class Randomer
    {
        public:
        static int GetRandom()
        {
            return distribution(generator);
        }
        static unsigned int GetRandom(unsigned int mod)
        {
            return GetRandom() % mod;
        }
        
        static bool CheckPercentage(int chance)
        {
            return chance > GetRandom();
        }

        //returns one option from the list
        template<typename T>
        static T GetOneOption(const std::initializer_list<T> & options)
        {
            const auto n_options =  options.size();
            const auto chosen = GetRandom(n_options);
            auto a = std::begin(options);
            std::advance(a,chosen);
            return *a;

        }
        private:
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution;
    };

}