# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++17 -O2
LDFLAGS =
DEVFLAGS = -std=c++17 -Wall -Wextra -Wsign-conversion -pedantic-errors -Werror -Wuninitialized -g3

# Makefile settings - Can be customized.
APPNAME = labwork14.app
APPNAMEDEV = labwork14dbg.app
EXT = .cpp
SRCDIR = .
OBJDIR = build/

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################

all: $(APPNAME) cleandep

dev: $(APPNAMEDEV) cleandepdev

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(APPNAMEDEV) : $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.odg)
	$(CC) $(DEVFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

%.dg: $(SRCDIR)/%$(EXT)
	@$(CPP) $(DEVFLAGS) $< -MM -MT $(@:%.dg=$(OBJDIR)/%.odg) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/%.odg: $(SRCDIR)/%$(EXT)
	$(CC) $(DEVFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

cleandepdev:
	$(RM) $(OBJ:$(OBJDIR)/%.odg=%.dg)