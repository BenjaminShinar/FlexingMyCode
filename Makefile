#determine OS
ifeq ($(OS), Windows_NT)
	CURR_OS = WIN
	OUTEXTEN=.exe
	DELCMD = del /q /s o
	
else
	CURR_OS = LIN
	OUTEXTEN=.out
	DELCMD = rm -fv
endif

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
CPP_ANSI=-std=c++2a

C_LINKER_FLAGS= -lm -pthread
C_LINKER_LRT= -lrt

LIBS_NAME = battle_tower battle controller mockmon_data moves types condition stats mockmon_exp
MAIN_NAME = main

PROJECTS = knights_tour product_without reverse_sentence  five_stars calculator roman_numerals
TARGETS1 = $(addprefix output/,$(addsuffix $(OUTEXTEN),$(PROJECTS)))   
all: $(TARGETS1)

########################################################
obj/%_test.o: test/%_test.cpp include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

output/%$(OUTEXTEN): obj/%.o obj/%_test.o
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) $(^) -o $(@)

obj/%.o: lib/%.cpp include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

obj/%_test.o: test/%_test.c include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

#################-EXAMPLES-####################

#output/%.out: examples/%.cpp
#	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) $(<) -o $(@)


########################################################

#runfiles/%.out: obj/%.o obj/%_test.o
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

#obj/%.o: lib/%.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

#obj/%_test.o: test/%_test.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

########################################################

output/knights_tour$(OUTEXTEN): obj/knights_tour.o
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)
		
obj/knights_tour.o: knights_tour.cpp
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -c -o $(@)

output/product_without$(OUTEXTEN): obj/product_without.o
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

obj/product_without.o: product_without.c
	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -c -o $(@)

output/reverse_sentence$(OUTEXTEN): obj/reverse_sentence.o
	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

obj/reverse_sentence.o: reverse_sentence.c
	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -c -o $(@)

output/five_stars$(OUTEXTEN): obj/five_stars.o
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

obj/five_stars.o: five_stars.cpp
	$(CPP) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -c -o $(@)
########################################################

.PHONY: clean 
clean:
	$(DELCMD) output\*.out output\*.exe obj\*.o



.PRECIOUS: obj/%.o obj/%_test.o obj2/%.o obj2/%_test.o
.DEFAULT_GOAL:=all 

#must be tab delimited, otherwise e get a missing seperator error#
#variables arne't qouatuion marks
#will print out the command, so don't pipe this.
#use ralative paths to c so it will work both regardless of computer (home or lab)
#sometimes we need -lm to inlude the math library

#for windows:
#mingw32-make.exe instead of make