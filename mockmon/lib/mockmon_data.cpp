#include "mockmon_data.h"
#include "random_gen.h"

#include <cmath>
#include <algorithm>

namespace mockmon
{
    //this is too big a  class, we need to seperate the functionally accross some stuff

    const MockmonSpecies &Mockmon::GetMockmonSpeciesData() const
    {
        return MockmonSpecies::AllMockmons.at(m_currentSpeciesId);
    }

    unsigned int Mockmon::GetCurrentLevel() const
    {
        return CurrentLevel;
    }

    bool Mockmon::IsAbleToBattle() const
    {
        return m_ableToBattle && CurrentBattleStats.Health.GetStat() > 0;
    }

    /**
 * @brief 
 * check if this mockmon is wild
 * a mockmon can go from wild to owned, but not the other way around
 * used when calculating xp and when 'catching' mockmon
 * @return true - doesn't have a trainer
 * @return false - had a trainer in the past
 */
    bool Mockmon::IsWild() const
    {
        return m_trainerHistory.empty();
    }

    void Mockmon::LoseSomehow()
    {
        m_ableToBattle = false;
    }

    void Mockmon::FullRestore()
    {
        CurrentBattleStats.Health.RestStatToMax();
        for (auto &stat : CurrentBattleStats.m_battleStats)
        {
            stat.second.ResetBoost();
        }
        m_ableToBattle = true;
    }

    bool Mockmon::TeachMove(moves::MoveId newMoveId)
    {
        if (m_Moveset.size() <= moves::EquipedMove::MaxMoves)
        {
            m_Moveset.push_back(moves::EquipedMove(moves::ConstantMove::AllMovesWrappers.at(newMoveId)));
            if (m_outputEvents)
            {
                std::cout << m_name << " learned [" << newMoveId << "]" << '\n';
            }
            return true;
        }
        if (m_outputEvents)
        {
            std::cout << m_name << " cant learn [" << newMoveId << "]" << '\n';
        }
        return false;
    }

    std::set<MockmonSpeciesId> Mockmon::GetPossibleEvolutions() const
    {
        std::set<MockmonSpeciesId> evolutions;
        for (const auto &fn : GetMockmonSpeciesData().PossibleEvolutionsFunctions)
        {
            if (auto ev = fn(*this))
            {
                evolutions.insert(ev.value());
            }
        }
        return evolutions;
    }
    void Mockmon::TryEvolve()
    {
        const auto possibleEvolutions{GetPossibleEvolutions()};
        if (!possibleEvolutions.empty())
        {
            m_currentSpeciesId = *std::begin(possibleEvolutions);
            UpdateBaseStats();
        }
    }
    /**
 * @brief 
 * returns changeble version of the move set, 
 * use in actual battle
 * @return std::vector<moves::EquipedMove>& 
 */
    std::vector<moves::EquipedMove> &Mockmon::GetMoveSet()
    {
        return m_Moveset;
    }

    /**
 * @brief 
 * return a none-changble version of the move set, 
 * use for making decisions
 * @return const std::vector<moves::EquipedMove>& 
 */
    const std::vector<moves::EquipedMove> &Mockmon::ViewMoveSet() const
    {
        return m_Moveset;
    }

    void Mockmon::GrantExperiencePoints(long points)
    {
        if (points <= 0)
            return;
        auto positivePoints = static_cast<unsigned long>(points);
        auto neededToNextLevelAbs = MockmonExp::TotalExperinceForLevel(CurrentLevel + 1, GetMockmonSpeciesData().SpeciesLevelUpGroup);
        auto neededToNextLevel = neededToNextLevelAbs - experience_points;

        if (positivePoints < neededToNextLevel)
        {
            experience_points += positivePoints;
        }
        else
        {
            auto reminder = positivePoints - neededToNextLevel;
            experience_points += neededToNextLevel;
            LevelUp();
            GrantExperiencePoints(reminder);
        }
    }
    MockmonExp Mockmon::CheckExperiencePoints() const
    {
        return MockmonExp{CurrentLevel, experience_points};
    }
    void Mockmon::LevelUp()
    {
        if (m_outputEvents)
        {
            std::cout << m_name << " level increase! [" << CurrentLevel << " -> " << (CurrentLevel + 1) << "]" << '\n';
        }
        ++CurrentLevel;
        UpdateBaseStats();
        LearnLevelUpMoves(CurrentLevel);
    }

    void Mockmon::UpdateBaseStats()
    {
        CurrentBattleStats.UpdateBattleStats(stats::MockmonStats(GetMockmonSpeciesData().MockmonSpeciesStats, IVs, EVs, CurrentLevel));
    }

    void TeachMoves(Mockmon &m, const std::vector<moves::MoveId> &mvs)
    {
        const auto &mvset = m.ViewMoveSet();
        for (const auto &mv : mvs)
        {
            if (!std::any_of(std::begin(mvset), std::end(mvset), [&](const moves::EquipedMove &knownMove)
                             { return knownMove.IsSameAs(mv); }))
            {
                m.TeachMove(mv);
            }
        }
    }

    void Mockmon::LearnLevelUpMoves(int newLevel)
    {
        const auto movesFromLevelUp = GetMockmonSpeciesData().LevelUpMoves;

        for (const auto &mvs : movesFromLevelUp)
        {
            if (mvs.first == newLevel)
            {
                TeachMoves(*this, mvs.second);
            }
        }
    }

    void Mockmon::LearnLevelUpMoves()
    {
        const auto movesFromLevelUp = GetMockmonSpeciesData().LevelUpMoves;

        for (const auto &mvs : movesFromLevelUp)
        {
            if (mvs.first <= CurrentLevel)
            {
                TeachMoves(*this, mvs.second);
            }
        }
    }
    void Mockmon::ChangeName(const std::string &newName)
    {
        m_name = newName;
    }
    std::string_view Mockmon::GetName() const
    {
        return m_name;
    }

    void Mockmon::GainEffortValueFromVictory(const Mockmon &defeatedMon)
    {
        EVs.GainEffortValueStats(defeatedMon.GetMockmonSpeciesData().MockmonSpeciesStats);
    }

    void Mockmon::GainExperienceFromVictory(const Mockmon &defeatedMon)
    {
        GainEffortValueFromVictory(defeatedMon);

        //https://bulbapedia.bulbagarden.net/wiki/Experience#Experience_gain_in_battle
        //exp = (a*t*b*e*L*p*f*V) / (7 *s)

        auto participatingPokemonInWinningTeam = 1;

        // auto ExtraFromAbility = false; //p
        // auto ExtraFromTraded = false; //t
        // auto IsPastEvolution = false; //v

        //t*e*p*f*v
        //originalOwner * Egg * powerSomething * Affection * PastEvolutin
        auto NominatorModifiers = 1;
        //a*b*L
        auto NominatorValue = defeatedMon.ExpFromDefeating();

        //7*s
        auto Denominator = 1 * participatingPokemonInWinningTeam; //number of participating pokmon;

        long xp = static_cast<long>(std::floor((NominatorValue * NominatorModifiers) / Denominator));
        if (m_outputEvents)
        {
            std::cout << AppendAll({GetName(), "gain", std::to_string(xp), "xp points!"}) << '\n';
        }
        GrantExperiencePoints(xp);
    }

    long Mockmon::ExpFromDefeating() const
    {
        const auto speciesXp = GetMockmonSpeciesData().SpeciesExp;
        const auto wildXpModifer = IsWild() ? 1.0 : 1.5;
        const auto xp = (CurrentLevel * speciesXp * wildXpModifer / 7.0);
        return std::floor(xp);
    }

    std::optional<std::size_t> Mockmon::GetCurrentTrainer() const
    {
        if (!m_trainerHistory.empty())
        {
            return m_trainerHistory.front();
        }
        return {};
    }

    const std::deque<std::size_t> &Mockmon::ViewAllPastTrainers() const
    {
        return m_trainerHistory;
    }

    void Mockmon::SetCurrentTrainer(std::size_t new_trainer)
    {
        if (auto v = GetCurrentTrainer())
        {
            if (v.value() == new_trainer)
                return;
        }
        m_trainerHistory.push_front(new_trainer);
    }

}