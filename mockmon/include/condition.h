#pragma once
#include "identifiers/condition_id.h"
#include "identifiers/stats_id.h"
#include "mockmon_conditions/base_conditon_pulse.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>


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
        bool IsAffiliatedWithCondition(ConditionId conditionId) const;
        double GetConditionalBoost(StatsTypes requestStat,bool attacking) const; //used for burn - attack, parylsis - speed, reflect - physical defence, screen - special at defence, etc...
        void CauseCondition(pulser_uq_ptr && pulser);
        void RemoveCondition(ConditionId conditionId);
        void RemoveAllConditions();
        //void CausePoison();
        //void CauseSleep();
        // int HP() const {return m_HP;};
        // void ChangeHealth(int amount );
        void PulseBeforeTurn();
        void PulseAfterTurn(); // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
        private:
        void RemoveAllDueConditions(); //remove non relevent conditions 
        std::vector<pulser_uq_ptr> m_spesific_conditions; //maybe std::varient? i don't want to store pointers!
    };
}