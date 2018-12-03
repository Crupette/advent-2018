SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf -ldecent-engine -lm
CPPFLAGS	:= -O2 -Wall -std=c++17 -I $(INCDIR) -Llib/

OUT		:= Snow-Invaders.out

.PHONY: build clean run

build: $(OBJFILES)
	$(CC) -o $(BINDIR)$(OUT) $(OBJFILES) $(CPPFLAGS) $(LIBS)
clean:
	$(MAKE) -C $(ENGINEDIR) clean
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/$(OUT)

run:
	$(MAKE) -C $(BINDIR)

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
