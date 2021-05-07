include_directories(include)
#find_package(fmt REQUIRED)
#include_directories(${fmt_INCLUDE_DIRS})

file(GLOB identifiers_src CONFIGURE_DEPENDS
"lib/identifiers/*.cpp"
)

add_library(mockmon lib/main.cpp lib/battle_tower.cpp lib/battle.cpp lib/controller.cpp lib/condition.cpp lib/mockmon_data.cpp lib/mockmon_exp.cpp lib/mockmon_species.cpp lib/moves.cpp lib/random_gen.cpp  lib/stats.cpp lib/types.cpp lib/evolution.cpp lib/speciesId.cpp lib/specialized_moves.cpp lib/arena.cpp lib/interfaces.cpp lib/trainer_ai.cpp 
            ${identifiers_src}) 