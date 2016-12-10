EXEC :=  run
SRC  :=  $(wildcard *.cpp)
OBJ  :=  $(patsubst %.cpp,%.o,$(SRC))
# Options
CC      := g++
CFLAGS  := 
GSL_DIR := $$TACC_GSL_INC
GRVY_DIR := $$TACC_GRVY_INC
LDFLAGS := -L$$TACC_GSL_LIB -L$$TACC_GRVY_LIB
LDLIBS  := -lgsl -lgslcblas -lgrvy
# Rules
$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
%.o: %.cpp
	$(CC) -I$(GSL_DIR)/gsl -I$(GSL_DIR) -I$(GRVY_DIR) $(CFLAGS) -c  $<
%.o: %.h
.PHONY: clobber clean neat echo
clobber: clean
	$(RM) $(EXEC)
clean: neat
	$(RM) $(OBJ)
neat:
	$(RM) *~ .*~
echo:
	@echo $(OBJ) 

