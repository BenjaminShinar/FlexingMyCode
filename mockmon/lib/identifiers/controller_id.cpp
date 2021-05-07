#include "identifiers/controller_id.h"

namespace mockmon::controller
{
    std::string Stringify(const controllerEnum ctrler)
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

    std::ostream &operator<<(std::ostream &os, const controllerEnum &e)
    {
        os << Stringify(e);
        return os;
    }

}