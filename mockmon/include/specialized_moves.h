#pragma once

#include "moves.h"
#include "mockmon_data.h"
#include "Battle.h"

#include "interfaces.h"
#include <functional>
namespace mockmon::moves
{
    //this is a move typedef
    using ExMove = std::function<void(Battle& battle, const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)>;

    //this should replace the BaseMoveclass
    class CompositeMove
    {

        std::vector<ExMove> MoveParts;
        static ExMove CreateDamagingMove();
    };
}