#include "moves.h"

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::moves
{
    const std::map<MoveId,BaseMove> BaseMove::AllMoves
    {
        //id,{id,type,accuracy,power, base pp,max pp}
        {MoveId::Tackle, BaseMove(MoveId::Tackle,types::Types::Normal,95,35,35,46)},
        {MoveId::WaterGun, BaseMove(MoveId::WaterGun,types::Types::Water,100,40,25,40)}
    };
  
}