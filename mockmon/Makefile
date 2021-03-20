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
CPP_ANSI=-std=c++17
#C_LINKER_FLAGS= 
C_LINKER_FLAGS= -lm -pthread -lrt


LIBS_NAME = battle_tower battle controller mockmon_data moves types condition stats mockmon_exp
MAIN_NAME = main
LIBS = $(addprefix obj/,$(addsuffix .o,$(LIBS_NAME)))   
MAIN = $(addprefix obj/,$(addsuffix .o,$(MAIN_NAME)))   

all: output/main.exe


########################################################

obj/main.o: lib/main.cpp 
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

obj/%.o: lib/%.cpp include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

obj/%_test.o: test/%_test.c include/%.h
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) -c $(<) -o $(@)

#################-EXAMPLES-####################

output/main.exe: $(MAIN) $(LIBS)
	$(CPP) $(CPP_ANSI) $(CPP_COMPILER_FLAGS) $(^) -o $(@)


########################################################

#runfiles/%.out: obj/%.o obj/%_test.o
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) $(^) -o $(@) $(C_LINKER_FLAGS)

#obj/%.o: lib/%.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

#obj/%_test.o: test/%_test.c include/%.h
#	$(CC) $(C_ANSI) $(C_COMPILER_FLAGS) -c $(<) -o $(@)

########################################################

########################################################

.PHONY: clean 
clean:
	del /q /s output\*.out output\*.exe obj\*.o
#rm -fv output/*.out obj/*.o obj/*core* ./*core* 



.PRECIOUS: obj/%.o obj/%_test.o obj2/%.o obj2/%_test.o
.DEFAULT_GOAL:=all 

#must be tab delimited, otherwise e get a missing seperator error#
#variables arne't qouatuion marks
#will print out the command, so don't pipe this.
#use ralative paths to c so it will work both regardless of computer (home or lab)
#sometimes we need -lm to inlude the math library
#h files arent always updated properly, depends on how many times they are included and which of the files is changed