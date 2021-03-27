#include "random_gen.h"

#include <chrono>

namespace mockmon::random
{
  
    std::uniform_int_distribution<unsigned int> Randomer::distribution(0,100);
    std::default_random_engine Randomer::generator(std::chrono::steady_clock::now().time_since_epoch().count());
}