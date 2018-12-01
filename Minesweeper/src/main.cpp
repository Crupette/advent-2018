#include <Engine/Base.h>

#include "ScreenGame.h"

int main(int argc, char** argv){
	DecentEngine::Base::addScreen(new ScreenGame());

	DecentEngine::Base::init("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 850, 60, 0);

	return 0;
}
