#pragma once
#include "identifiers/pulsing_conditions_id.h"
#include "identifiers/non_pulsing_conditions_id.h"
#include "identifiers/stats_id.h"
#include "identifiers/moves_id.h"
#include "mockmon_conditions/base_conditon_pulse.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <set>
#include <optional>

namespace mockmon::condition
{
  using pulser_uq_ptr = std::unique_ptr<ConditonPulseEffect>;

  //non voltile conditions, paralyzed, burn, freeze, poision, toxic
  // also voltaile conditions, at least for now

  //maybe the command desgin pattern?

  /*
    burn - check before using an attack? if burned, half attacking stat? cause damage after turn? maybe we can be drenshed out by 
    sleep - check before using an attack? if asleep, do nothing attack? maybe have a 'wakeup' attack that we check?
    frozen - check before using an attack, if frozen, do nothing attack, but we need to check if an incoming attack thaws us?
    poison - check after turn, cause damage? maybe faint?
    badly poison - check after turn, cause damage? maybe faint? increase the damage counter?
  */

  class Condition
  {
  public:
    [[nodiscard]] bool IsAffiliatedWithCondition(PulsingConditionId pulsingConditiondId) const;
    [[nodiscard]] bool IsAffiliatedWithCondition(NonPulsingConditionId nonepulsingConditiondId) const;

    [[nodiscard]] double GetConditionalBoost(StatsTypes requestStat, bool attacking) const;
    void CausePulsingCondition(pulser_uq_ptr &&pulser);
    void CauseNonPulsingCondition(NonPulsingConditionId nonepulsingConditiondId);
    void RemovePulsingCondition(PulsingConditionId pulsingConditiondId);
    void RemoveAllConditions();
    void PulseBeforeTurn();
    void PulseAfterTurn(); // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
    [[nodiscard]] std::optional<moves::MoveId> GetChargedMove();
    void StoreChargedMove(moves::MoveId mvId);

  private:
    void RemoveAllDueConditions();                    //remove non relevent conditions
    std::vector<pulser_uq_ptr> m_spesific_conditions; //maybe std::varient? std::set? i don't want to store pointers! how to polymorphism better?
    std::set<NonPulsingConditionId> m_nonPulseCondtions;
    std::stack<moves::MoveId> m_chargedMoves;
  };
}