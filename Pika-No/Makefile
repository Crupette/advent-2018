SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/
ENGINEDIR	:= Engine/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf -ldecent-engine -lm -lSDL2_mixer
CPPFLAGS	:= -Wall -std=c++17 -I $(INCDIR) -Llib/

OUT		:= Pika-No.out

.PHONY: build clean run

build: $(OBJFILES)
	$(MAKE) -C $(ENGINEDIR) build
	cp -r $(ENGINEDIR)bin/libdecent-engine.a lib/libdecent-engine.a
	$(CC) -o $(BINDIR)$(OUT) $(OBJFILES) $(CPPFLAGS) $(LIBS)
clean:
	$(MAKE) -C $(ENGINEDIR) clean
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)/$(OUT)

run:
	$(MAKE) -C $(BINDIR)

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
