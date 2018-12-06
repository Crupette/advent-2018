#include "GuiHud.h"
#include "ScreenGame.h"
#include "Player.h"

#include <Engine/InputManager.h>

GuiHud::GuiHud() : Gui(DecentEngine::Gui::Type::CONST) {

}

GuiHud::~GuiHud(){

}

void GuiHud::update(){
	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
		mousepos = glm::uvec2(mousepos.x, 768 - mousepos.y);

		if(mousepos.x > 5 && mousepos.x < 400 && mousepos.y > 5 && mousepos.y < 26){
			if(Player::money >= 10){
				Player::money -= 10;
				Player::maxDepth++;
			}
		}
	}
}

void GuiHud::render(){
	ScreenGame::fontRenderer.renderText(std::string("Gold: ") + std::to_string(Player::money), glm::vec2(5, 768 - 42), glm::vec2(1), glm::uvec4(255));
	ScreenGame::fontRenderer.renderText(std::string("Maximum Depth: ") + std::to_string(Player::maxDepth * 100), glm::vec2(5, 768 - 74), glm::vec2(1), glm::uvec4(255));
	ScreenGame::fontRenderer.renderText("Click here to upgrade maximum depth for 10 gold", glm::vec2(5, 5), glm::vec2(0.5f), glm::uvec4(0, 255, 0, 255));
}
