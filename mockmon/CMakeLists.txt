include_directories(include)
#find_package(fmt REQUIRED)
#include_directories(${fmt_INCLUDE_DIRS})

file(GLOB identifiers_dictionaries_src CONFIGURE_DEPENDS
"lib/identifiers/*.cpp"
"lib/constants dictionaries/*.cpp"
"lib/game_driver/*.cpp"
"lib/stats/*.cpp"
)


add_library(mockmon lib/battle.cpp lib/condition.cpp lib/mockmon_data.cpp lib/mockmon_exp.cpp lib/mockmon_species.cpp lib/moves.cpp lib/random_gen.cpp lib/types.cpp lib/evolution.cpp lib/speciesId.cpp lib/specialized_moves.cpp lib/arena.cpp lib/interfaces.cpp lib/trainer_ai.cpp
            lib/damage_calculations.cpp
            ${identifiers_dictionaries_src}) 