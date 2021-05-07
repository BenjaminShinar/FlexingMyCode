#pragma once
#include <string.h>
#include <iostream>
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
}