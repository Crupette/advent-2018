#include <Engine/Base.h>

#include "ScreenGame.h"

int main(int argc, char** argv){
	DecentEngine::Base::addScreen(new ScreenGame());

	DecentEngine::Base::init("Elf off the Shelf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 60, 0);

	return 0;
}
