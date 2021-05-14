#pragma once
#include "identifiers/condition_id.h"
#include <string>
#include <iostream>



namespace mockmon::condition
{
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
        void CauseCondition(ConditionId conditionId);
        void RemoveCondition(ConditionId conditionId);
        //void CausePoison();
        //void CauseSleep();
        // int HP() const {return m_HP;};
        // void ChangeHealth(int amount );
        void PulseTurn(); // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
        private:
        bool m_isPoisioned{false};
        //int m_HP = 50;
    };
}