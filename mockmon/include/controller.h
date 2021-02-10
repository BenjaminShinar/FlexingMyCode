#pragma once
//#include <string_view>
#include <string>
namespace mockmon::controller
{

    enum controller
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

    std::string controllerToStr(const controller ctrler)
    {
        switch (ctrler)
        {
            case DPAD_UP: return "UP";
            case DPAD_LEFT: return "LEFT";
            case DPAD_DOWN: return "DOWN";
            case DPAD_RIGHT: return "RIGHT";
            case ACTION_A: return "A";
            case CANCEL_B: return "B";
            case START: return "START";
            case SELECT: return "SELECT";
            default: return "nothing";
        }
    }

    // controller strToController(std::string_view & str)
    // {
    //     switch (str)
    //     {
    //         case "UP": return DPAD_UP;
    //         case "LEFT": return DPAD_LEFT;
    //         case "DOWN": return DPAD_DOWN;
    //         case "RIGHT": return DPAD_RIGHT;
    //         case "A": return ACTION_A:
    //         case "B": return CANCEL_B;
    //         case "START": return START:
    //         case "SELECT": return SELECT:;
    //         default: return SELECT;
    //     }
    // }
}