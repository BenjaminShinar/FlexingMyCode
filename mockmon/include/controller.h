#pragma once
#include <string>
#include <array>
#include <utility>
#include <iostream>
#include <map>
#include <vector>
namespace mockmon::controller
{
    //think about a way to put all the enums somewhere else, maybe template their << operator
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
    std::ostream& operator<<(std::ostream& os,const controllerEnum& ctrl);
    std::string controllerToStr(const controllerEnum ctrler);
    void TestControllerToString();
    unsigned int ReadInput(std::size_t max);

    /* has to be defined here because it uses a template argument*/
    template <typename T,std::size_t N>
    T GetAnyInput(const std::string &prompt, const std::array<std::pair<std::string, T>, N> & options)
    {
        std::cout << prompt << '\n';
        auto d = ReadInput(N);
        const auto p = options.at(d);
        std::cout << p.first << " : " << p.second << '\n';
        return p.second;
    }

    template <typename T>
    auto GetAnyInput(const std::string &prompt, const std::vector<T> & options)
    {
        std::cout << prompt << '\n';
        auto d = ReadInput(options.size());
        const auto p = options.at(d);
        std::cout << p.Describe() << '\n';
        return p.Identifier();
    }
 }