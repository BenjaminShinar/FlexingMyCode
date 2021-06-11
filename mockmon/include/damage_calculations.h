#pragma once

#include "identifiers/moves_id.h"
#include "identifiers/type_effectiveness_id.h"
#include "mockmon_data.h"
namespace mockmon::battle
{
    /**
     * @brief Get the Level Damage Modifier
     * how levels effect damage
     * @param m the attacking mockmon
     * @return double 
     */
    double GetLevelDamageModifier(const Mockmon & m);
    /**
     * @brief Get the Level Critical Damage Modifier 
     * how levels effect damage in critical hits
     * @param m the attacking mockmon
     * @return double 
     */
    double GetLevelCriticalDamageModifier(const Mockmon & m);

    /**
     * @brief Get the Stab Damage Modifier 
     * how stab stab damage is modified
     * @param isStab 
     * @return double 
     */
    double GetStabDamageModifier(bool isStab);
    
    /**
     * @brief Get the Type Effetiveness Modifier 
     * how the type effectiness is translated into damage
     * @param modifier 
     * @return double 
     */
    double GetTypeEffetivenessModifier(types::TypeEffectivenessModifier modifier);

    /**
     * @brief Get the Damage Ranges object
     * a random modifer
     * @return double 
     */
    double GetDamageRanges();
}