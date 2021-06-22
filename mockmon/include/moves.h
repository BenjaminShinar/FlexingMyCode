#pragma once

#include "types.h"
#include "identifiers/moves_id.h"
#include "identifiers/priority_id.h"
#include "interfaces.h"

#include <string>
#include <string_view>
#include <iostream>
#include <map>
#include <optional>

namespace mockmon::moves
{

    //not used
    enum class MovesDamageTypes
    {
        NormalDamage,
        AugmentedAmount, // damage based on the normal amount, and other parts?
        FixedAmount,     //always the same
        ScalingAmount,   //based on a stat that isn't attack/defence/special
        OneHitKnockOut   //all the damage
    };

    //unique move name
    [[nodiscard]] types::Types GetMoveType(moves::MoveId mvId);
    struct BaseMove : public IdentifiybleModule<moves::MoveId>
    {
        explicit BaseMove(moves::MoveId moveId, types::Types type) : IdentifiybleModule(moveId),
                                                                     Type(type)
        {
        }

        const types::Types Type;
    };

    struct SimpleMove : public BaseMove
    {
        //do I really need this? can someone else take care of base power? for me?
        const unsigned int BasePower;

        static const std::map<moves::MoveId, SimpleMove> AllMoves;
        explicit SimpleMove(moves::MoveId moveId, types::Types type, unsigned int power) : BaseMove(moveId, type), BasePower(power)
        {
        }
    };

    /**
     * @brief 
     * this is the move constant usage data - base and max power points
     */
    struct ConstantMove : public IdentifiybleModule<moves::MoveId>
    {
        const unsigned int BaseStartingPowerPoints;
        const unsigned int BaseMaxPowerPoints;

        static const std::map<moves::MoveId, ConstantMove> AllMovesWrappers;

        explicit ConstantMove(moves::MoveId moveId, unsigned int basePP, unsigned int maxPP) : IdentifiybleModule(moveId),
                                                                                               BaseStartingPowerPoints(basePP), BaseMaxPowerPoints(maxPP)
        {
        }
    };

    //this is the move when it's on a pokemon
    class EquipedMove : public DescribleModule<moves::MoveId>
    {
    public:
        explicit EquipedMove(const ConstantMove &constantMove) : DescribleModule(constantMove.Identifier()),
                                                                 BaseMoveStats(constantMove), m_fullPowerPoints(constantMove.BaseStartingPowerPoints),
                                                                 m_currentPowerPoints(constantMove.BaseStartingPowerPoints)
        {
        }

        const ConstantMove &BaseMoveStats; //what move it refers to, constant db of moves;
        [[nodiscard]] unsigned int RemainningPowerPoints() const;

        std::optional<moves::MoveId> UseMove();
        std::string Describe() const override;

        //these probably belong with a friend class;

        [[nodiscard]] bool IncreasePowerPoints();
        void RefillPowerPoints();

        static constexpr std::size_t MaxMoves = 15;

    private:
        unsigned int m_fullPowerPoints;
        unsigned int m_currentPowerPoints;
    };

    [[nodiscard]] bool CheckMoveAccuracy(const SimpleMove &attack);
    [[nodiscard]] double CriticalChanceBoost(moves::MoveId mvId);
    [[nodiscard]] Priority GetMovePriority(moves::MoveId mvId);

}
