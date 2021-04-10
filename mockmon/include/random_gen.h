#pragma once

#include <random>

namespace mockmon::random
{
   
    class Randomer
    {
        public:
        static unsigned int GetRandom()
        {
            return distribution(generator);
        }
        static unsigned int GetRandom(unsigned int mod)
        {
            return GetRandom() % mod;
        }
        private:
        static std::default_random_engine generator;
        static std::uniform_int_distribution<unsigned int> distribution;
    };

}