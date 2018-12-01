SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/
ENGINEDIR	:= ../Decent-Engine/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf
CPPFLAGS	:= -Wall -Werror -std=c++17 -I $(INCDIR) -L $(ENGINEDIR)bin/

OUT		:= Asteroids.out

.PHONY: build clean run

build: $(OBJFILES)
	$(MAKE) -C $(ENGINEDIR) build
	@echo Building tester
	$(CC) $(CPPFLAGS) $(LIBS) -o $(BINDIR)$(OUT) $(OBJFILES) $(ENGINEDIR)bin/Decent-Engine.a
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
