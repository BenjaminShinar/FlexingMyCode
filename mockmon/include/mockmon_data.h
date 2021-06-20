#pragma once

#include "identifiers/trainer_ai_id.h"
#include "moves.h"
//#include <string_view>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <optional>

#include "condition.h"
#include "stats/stats.h"
#include "stats/battle_stats.h"
#include "mockmon_species.h"
#include "mockmon_exp.h"

namespace mockmon
{
    class Mockmon
    {
        friend class Battle;
        friend class Arena;

    public:
        explicit Mockmon(MockmonSpeciesId species, const std::string &name, bool silent = false)
            : m_currentSpeciesId(species), m_name(name), m_outputEvents(silent)
        {
            LearnLevelUpMoves(1);
            CurrentBattleStats.UpdateBattleStats(stats::MockmonStats(GetMockmonSpeciesData().MockmonSpeciesStats, IVs, EVs, CurrentLevel));
            CurrentBattleStats.m_battleStats.at(StatsTypes::CriticalHitChance).ChangeStat(GetMockmonSpeciesData().MockmonSpeciesStats.Stats.Speed); //critical hit chance for species
            CurrentBattleStats.Health.RestStatToMax();                                                                                              //max health at creation
        }

        unsigned int GetCurrentLevel() const;
        const MockmonSpecies &GetMockmonSpeciesData() const;
        void ChangeName(const std::string &newName); //needs to be somewhere else.
        void GrantExperiencePoints(long points);
        MockmonExp CheckExperiencePoints() const;
        long ExpFromDefeating() const;
        void GainEffortValueFromVictory(const Mockmon &defeatedMon);
        void GainExperienceFromVictory(const Mockmon &defeatedMon);
        void LoseSomehow();
        void FullRestore();
        bool IsAbleToBattle() const;
        bool IsWild() const { return false; }
        bool TeachMove(moves::MoveId);

        std::vector<moves::EquipedMove> &GetMoveSet();
        const std::vector<moves::EquipedMove> &ViewMoveSet() const;

        std::string_view GetName() const;
        bool DisplayEvent() const { return m_outputEvents; }
        //battle relatedStuff probably alot of methods should go somewhere else
        std::set<MockmonSpeciesId> GetPossibleEvolutions() const;
        void TryEvolve();

        std::optional<unsigned int> GetCurrentTrainer() const;
        const std::deque<unsigned int> &ViewAllPastTrainers() const;
        void SetCurrentTrainer(unsigned int new_trainer);

    private:
        void LearnLevelUpMoves();
        void LearnLevelUpMoves(int level);
        void LevelUp();
        void UpdateBaseStats();

    public:
        condition::Condition m_currentCondtion{};
        stats::BattleStats CurrentBattleStats; // this is calculated each level;

    protected:
    private:
        MockmonSpeciesId m_currentSpeciesId; //this can change when the mockmon evolves

        std::string m_name;
        bool m_outputEvents;
        int CurrentLevel = 1;
        long experience_points = 0;
        bool m_ableToBattle = true;
        std::vector<moves::EquipedMove> m_Moveset;
        const stats::IndividualStats IVs;          //this is calculated once when the pokemon is born;
        stats::EffortValuesStats EVs;              // this is what we gain after each battle;
        std::deque<unsigned int> m_trainerHistory; // did this mockmon have previous owners?
    };
}
