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

    void TestControllerToString()
    {
        std::cout << controllerToStr(controllerEnum::DPAD_UP) << '\n';
        std::cout << controllerToStr(controllerEnum::DPAD_LEFT) << '\n';
        std::cout << controllerToStr(controllerEnum::DPAD_DOWN) << '\n';
        std::cout << controllerToStr(controllerEnum::DPAD_RIGHT) << '\n';
        std::cout << controllerToStr(controllerEnum::ACTION_A) << '\n';
        std::cout << controllerToStr(controllerEnum::CANCEL_B) << '\n';
        std::cout << controllerToStr(controllerEnum::START) << '\n';
        std::cout << controllerToStr(controllerEnum::SELECT) << '\n';
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