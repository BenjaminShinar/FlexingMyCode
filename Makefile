#user flags:
DFLAG=

ifeq ($(DFLAG),O3)
	C_OPTIMIZING=-DNDEBUG -O3
	CPP_OPTIMIZING=-DNDEBUG -O3
	=
else 
ifeq ($(DFLAG),prof)
	C_OPTIMIZING=-pg
	CPP_OPTIMIZING=-pg
	else
	C_OPTIMIZING=-g 
	CPP_OPTIMIZING=-g
endif
endif
	
#
CC = gcc
CPP = g++
SHELL = /bin/bash

C_COMPILER_FLAGS=$(WARNING_LEVEL) -fpic $(C_OPTIMIZING) -I./include/
CPP_COMPILER_FLAGS=$(WARNING_LEVEL) -Weffc++ -fpic $(CPP_OPTIMIZING) -I./include/
WARNING_LEVEL=-pedantic-errors -Wall -Wextra
C_ANSI=-ansi
CPP_ANSI=-std=c++11
#C_LINKER_FLAGS= 
C_LINKER_FLAGS= -lm -pthread -lrt

all: knights_tour.out


########################################################
obj/%.o: lib/%.cpp include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

obj/%_test.o: test/%_test.cpp include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

output/%.out: obj/%.o obj/%_test.o
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

obj/%.o: lib/%.cpp include/%.hpp
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

obj/%_test.o: test/%_test.cpp include/%.hpp
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

#################-EXAMPLES-####################

output/%.out: examples/%.cpp
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) $(<) -o $(@)


########################################################

#runfiles/%.out: obj/%.o obj/%_test.o
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

#obj/%.o: lib/%.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

#obj/%_test.o: test/%_test.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

########################################################


knights_tour.out: obj/knights_tour.o
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

obj/knights_tour.o: knights_tour.cpp
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -c -o $(@)

########################################################

.PHONY: clean 
clean:
	rm -fv output/*.out obj/*.o obj/*core* ./*core* 



.PRECIOUS: obj/%.o obj/%_test.o obj2/%.o obj2/%_test.o
.DEFAULT_GOAL:=all 

#must be tab delimited, otherwise e get a missing seperator error#
#variables arne't qouatuion marks
#will print out the command, so don't pipe this.
#use ralative paths to c so it will work both regardless of computer (home or lab)
#sometimes we need -lm to inlude the math library
