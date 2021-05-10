#include "types.h"
#include "interfaces.h"
#include <vector>
namespace mockmon::types
{

    using v_t= vector_type_T<types::Types>;       
    std::map<Types,TypeEffectivness> TypeEffectivness::TypeEffectiveChart
    {
        
        MakeDictionaryPair<TypeEffectivness>(Types::Typeless,v_t{},v_t{},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Normal,v_t{},v_t{Types::Rock,Types::Steel},v_t{Types::Ghost}),
        MakeDictionaryPair<TypeEffectivness>(Types::Fire,v_t{Types::Grass,Types::Ice,Types::Bug, Types::Steel},v_t{Types::Fire,Types::Water,Types::Rock,Types::Dragon},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Water,v_t{Types::Fire,Types::Ground,Types::Rock},v_t{Types::Water,Types::Grass,Types::Dragon},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Electric,v_t{Types::Water,Types::Flying},v_t{Types::Electric,Types::Ground,Types::Dragon},v_t{Types::Ground}),
        MakeDictionaryPair<TypeEffectivness>(Types::Grass,v_t{Types::Water,Types::Rock,Types::Ground},v_t{Types::Fire,Types::Fire,Types::Poison,Types::Bug,Types::Dragon,Types::Steel},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Ice,v_t{Types::Grass,Types::Ground,Types::Flying,Types::Dragon},v_t{Types::Fire,Types::Water,Types::Ice,Types::Steel},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Fighting,v_t{Types::Normal,Types::Ice,Types::Rock,Types::Dark,Types::Steel},v_t{Types::Poison,Types::Flying,Types::Psychic,Types::Bug,Types::Fairy},v_t{Types::Ghost}),
        MakeDictionaryPair<TypeEffectivness>(Types::Poison,v_t{Types::Grass,Types::Fairy},v_t{Types::Poison,Types::Flying,Types::Rock,Types::Ghost},v_t{Types::Steel}),
        MakeDictionaryPair<TypeEffectivness>(Types::Ground,v_t{Types::Fire,Types::Electric,Types::Poison,Types::Rock,Types::Steel},v_t{Types::Grass,Types::Bug},v_t{Types::Ground}),
        MakeDictionaryPair<TypeEffectivness>(Types::Flying,v_t{Types::Grass,Types::Fighting,Types::Bug},v_t{Types::Electric,Types::Rock,Types::Steel},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Psychic,v_t{Types::Fighting,Types::Poison},v_t{Types::Bug,Types::Steel},v_t{Types::Dark}),        
        MakeDictionaryPair<TypeEffectivness>(Types::Bug,v_t{Types::Grass,Types::Psychic,Types::Dark},v_t{Types::Fire,Types::Fighting,Types::Poison,Types::Flying,Types::Ghost,Types::Steel,Types::Fairy},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Rock,v_t{Types::Water,Types::Ice,Types::Flying,Types::Bug},v_t{Types::Fighting,Types::Ground,Types::Steel},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Ghost,v_t{Types::Psychic,Types::Ghost},v_t{Types::Dark},v_t{Types::Normal}),
        MakeDictionaryPair<TypeEffectivness>(Types::Dragon,v_t{Types::Dragon},v_t{Types::Steel},v_t{Types::Fairy}),
        MakeDictionaryPair<TypeEffectivness>(Types::Dark,v_t{Types::Psychic,Types::Ghost},v_t{Types::Fighting,Types::Dark,Types::Fairy},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Steel,v_t{Types::Ice,Types::Rock,Types::Fairy},v_t{Types::Fire,Types::Water,Types::Electric,Types::Steel},v_t{}),
        MakeDictionaryPair<TypeEffectivness>(Types::Fairy,v_t{Types::Fighting,Types::Dragon,Types::Dark},v_t{Types::Fire,Types::Poison,Types::Steel},v_t{})
     };
}