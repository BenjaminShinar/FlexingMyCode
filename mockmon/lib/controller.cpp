#include "controller.h"

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::controller
{
    
    void TestControllerToString()
    {
        std::cout << controllerEnum::DPAD_UP << '\n';
        std::cout << controllerEnum::DPAD_LEFT << '\n';
        std::cout << controllerEnum::DPAD_DOWN << '\n';
        std::cout << controllerEnum::DPAD_RIGHT << '\n';
        std::cout << controllerEnum::ACTION_A << '\n';
        std::cout << controllerEnum::CANCEL_B << '\n';
        std::cout << controllerEnum::START << '\n';
        std::cout << controllerEnum::SELECT << '\n';
    }

    unsigned int ReadInput(std::size_t Max)
    {
        auto d = 1u;
        std::string s;

        do
        {
            std::getline(std::cin, s);
            std::istringstream is(s);
            is >> d;
            std::cout << "input read is " << d << '\n';
        } while (d <= 0 || d > Max);
        return d - 1;
    }
}