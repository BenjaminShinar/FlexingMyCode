#pragma once
#include <string>
#include <array>
#include <utility>
#include <iostream>
namespace mockmon::controller
{
    
    enum class controllerEnum
    {
        DPAD_UP,
        DPAD_LEFT,
        DPAD_DOWN,
        DPAD_RIGHT,
        ACTION_A,
        CANCEL_B,
        START,
        SELECT
    };

    std::string controllerToStr(const controllerEnum ctrler);
    void TestControllerToString();
    unsigned int ReadInput(std::size_t max);


    /* has to be defined here because it uses a template argument*/
    template <std::size_t N>
    controllerEnum GetInput(const std::string &prompt, const std::array<std::pair<std::string, controller::controllerEnum>, N> & actions)
    {
        std::cout << prompt << '\n';
        auto d = ReadInput(N);
        const auto p = actions.at(d);
        std::cout << p.first << " : " << controllerToStr(p.second) << '\n';
        return p.second;
    }
}