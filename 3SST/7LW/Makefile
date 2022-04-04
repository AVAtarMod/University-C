# Compiler settings - Can be customized.
CC = g++
LIB_PATH = -iquote ~/Programming/C++/Includes
CXXFLAGS = -std=c++17 -O2 $(LIB_PATH)
LDFLAGS =
DEVFLAGS = -std=c++17 -Wall -Wextra -Wsign-conversion -pedantic-errors -Werror -Wuninitialized -g3  -Wno-error=unused-but-set-parameter -Wno-error=unused-parameter $(LIB_PATH)

# Makefile settings - Can be customized.
APPNAME = realease.app
APPNAMEDEV = debug.app
EXT = .cpp
SRCDIR = .
OBJDIR = build/

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

SRCDEV = $(wildcard $(SRCDIR)/*$(EXT))
OBJDEV = $(SRCDEV:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.odg)
DEPDEV = $(OBJDEV:$(OBJDIR)/%.odg=%.dg)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)

DELOBJDEV = $(OBJDEV)

########################################################################
####################### Targets beginning here #########################

all: $(APPNAME) cleandep cleandepdev

dev: $(APPNAMEDEV) cleandepdev cleandep

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(APPNAMEDEV): $(OBJDEV)
	$(CC) $(DEVFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

%.dg: $(SRCDIR)/%$(EXT)
	@$(CPP) $(DEVFLAGS) $< -MM -MT $(@:%.dg=$(OBJDIR)/%.odg) >$@

# Includes all .h files
-include $(DEP)

-include $(DEPDEV)

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

.PHONY: cleandepdev
cleandepdev:
	$(RM) $(DEPDEV)
