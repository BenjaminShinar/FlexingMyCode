#include "controller.h"

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::controller
{

    std::string controllerToStr(const controller::controllerEnum ctrler)
    {
        switch (ctrler)
        {
        case controllerEnum::DPAD_UP:
            return "UP";
        case controllerEnum::DPAD_LEFT:
            return "LEFT";
        case controllerEnum::DPAD_DOWN:
            return "DOWN";
        case controllerEnum::DPAD_RIGHT:
            return "RIGHT";
        case controllerEnum::ACTION_A:
            return "A";
        case controllerEnum::CANCEL_B:
            return "B";
        case controllerEnum::START:
            return "START";
        case controllerEnum::SELECT:
            return "SELECT";
        default:
            return "nothing";
        }
    }

   std::ostream& operator<<(std::ostream& os,const controllerEnum& ctrl)
    {
        os << controllerToStr(ctrl);
        return os;
    }
    
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