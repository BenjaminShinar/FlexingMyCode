#include "stats/stats.h"
#include <cmath>
namespace mockmon::stats
{

  double BoostFromStatModifierLevel(StatModifiersLevels modifierLevel)
  {
    switch (modifierLevel)
    {
    case StatModifiersLevels::Lowest:
      return 0.25;
      break;
    case StatModifiersLevels::DecresedEvenFurther:
      return 0.28;
      break; //28/100
    case StatModifiersLevels::DecreasedMuchFurther:
      return 0.33;
      break; // 33/100
    case StatModifiersLevels::DecreasedSeverly:
      return 0.4;
      break; //40/100
    case StatModifiersLevels::GreatlyDecreased:
      return 0.5;
      break; //50/100
    case StatModifiersLevels::Decrese:
      return 0.66;
      break; //66/100
    case StatModifiersLevels::Normal:
      return 1.0;
      break; //100/100
    case StatModifiersLevels::Increase:
      return 1.5;
      break; //150/100
    case StatModifiersLevels::GreatlyIncrease:
      return 2.0;
      break; //200/100
    case StatModifiersLevels::IncreasedDrastically:
      return 2.5;
      break; //250/100
    case StatModifiersLevels::IncreasedMuchFurther:
      return 3.0;
      break; //300/100
    case StatModifiersLevels::IncreasedEvenFurther:
      return 3.5;
      break; //350/100
    case StatModifiersLevels::Highest:
      return 4.0;
      break; //400/100
    default:
      return 1.0;
      break;
    }
  }

  //this is what happens in after a fight
  void EffortValuesStats::GainEffortValueStats(const SpeciesBaseStats &enemiesBaseStats)
  {
    Stats.Health = std::min(Stats.Health + enemiesBaseStats.Stats.Health, MaxStatValue);
    Stats.Attack = std::min(Stats.Attack + enemiesBaseStats.Stats.Attack, MaxStatValue);
    Stats.Defence = std::min(Stats.Defence + enemiesBaseStats.Stats.Defence, MaxStatValue);
    Stats.Special = std::min(Stats.Special + enemiesBaseStats.Stats.Special, MaxStatValue);
    Stats.Speed = std::min(Stats.Speed + enemiesBaseStats.Stats.Speed, MaxStatValue);
  }

  //this is the level up stats Increase
  MockmonStats::MockmonStats(const SpeciesBaseStats &speciesBaseStats, const IndividualStats &IVStats, const EffortValuesStats &EVStats, unsigned int level)
  {
    Stats.Health = std::min(ModifyStat(speciesBaseStats.Stats.Health, IVStats.Stats.Health, EVStats.Stats.Health, level) + level + 10, MaxStatValue);
    Stats.Attack = std::min(ModifyStat(speciesBaseStats.Stats.Attack, IVStats.Stats.Attack, EVStats.Stats.Attack, level) + 5, MaxStatValue);
    Stats.Defence = std::min(ModifyStat(speciesBaseStats.Stats.Defence, IVStats.Stats.Defence, EVStats.Stats.Defence, level) + 5, MaxStatValue);
    Stats.Special = std::min(ModifyStat(speciesBaseStats.Stats.Special, IVStats.Stats.Special, EVStats.Stats.Special, level) + 5, MaxStatValue);
    Stats.Speed = std::min(ModifyStat(speciesBaseStats.Stats.Speed, IVStats.Stats.Speed, EVStats.Stats.Speed, level) + 5, MaxStatValue);
  }

  unsigned int MockmonStats::ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level)
  {

    auto stat = ((2.0 * (base + iv)) + (sqrt(ev) / 4.0)) * level / 100.0;
    return std::floor(stat);
  }
}