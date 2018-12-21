#include <Engine/Base.h>

#include "ScreenGame.h"

int main(int argc, char** argv){
	DecentEngine::Base::addScreen(new ScreenGame());

	DecentEngine::Base::init("Block Sliders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, 60, 0);

	return 0;
}
