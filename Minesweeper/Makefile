SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/
ENGINEDIR	:= ../Decent-Engine/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf -ldecent-engine
CPPFLAGS	:= -Wall -Werror -std=c++17 -I $(INCDIR) -L $(ENGINEDIR)bin/

OUT		:= Minesweeper.out

.PHONY: build clean run

build: $(OBJFILES)
	$(MAKE) -C $(ENGINEDIR) build
	@echo Building tester
	$(CC) -o $(BINDIR)$(OUT) $(OBJFILES) $(CPPFLAGS) $(LIBS)
	@echo Liked obj files to $(BINDIR)$(OUT)
clean:
	@echo Cleaning temporary and built files
	$(MAKE) -C $(ENGINEDIR) clean
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/$(OUT)

run:
	$(MAKE) -C $(BINDIR)

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	@echo Compiling $< into $@
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
