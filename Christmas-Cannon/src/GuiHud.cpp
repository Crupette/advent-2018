#include "GuiHud.h"
#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>

GuiHud::GuiHud() : DecentEngine::Gui(DecentEngine::Gui::Type::CONST) {
	
}

GuiHud::~GuiHud(){
	
}

void GuiHud::update(){
	ScreenGame* game = static_cast<ScreenGame*>(DecentEngine::Base::getScreen(0));

	glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
	mousepos.y = 768 - mousepos.y;

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		printf("Press %i, %i\n", mousepos.x, mousepos.y);
	}

	if(mousepos.x > 5 && mousepos.x < 256 && mousepos.y > 768 - 69 && mousepos.y < 768 - 37){
		if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
			game->buyPower();
		}
	}

	if(mousepos.x > 5 && mousepos.x < 256 && mousepos.y > 768 - 101 && mousepos.y < 768 - 69){
		if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
			game->buyAero();
		}
	}
}

void GuiHud::render(){
	ScreenGame* game = static_cast<ScreenGame*>(DecentEngine::Base::getScreen(0));
	
	ScreenGame::fontRenderer.renderText(std::string("$") + std::to_string(game->getMoney()), glm::vec2(5.f, 768.f - 37.f), glm::vec2(1.f), glm::uvec4(0, 255, 0, 255));
	ScreenGame::fontRenderer.renderText(std::string("More Power: $") + std::to_string(game->getCostPower()), glm::vec2(5.f, 768.f - 69.f), glm::vec2(1.f), glm::uvec4(255));
	ScreenGame::fontRenderer.renderText(std::string("More Aerodynamics: $") + std::to_string(game->getCostAero()), glm::vec2(5.f, 768.f - 101.f), glm::vec2(1.f), glm::uvec4(255));
}
