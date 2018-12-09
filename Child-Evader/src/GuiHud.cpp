#include "GuiHud.h"
#include "ScreenGame.h"

#include <Engine/Base.h>

GuiHud::GuiHud() : DecentEngine::Gui(DecentEngine::Gui::Type::CONST){

}
GuiHud::~GuiHud(){

}

void GuiHud::init(){

}
void GuiHud::update(){

}
void GuiHud::render(){
	double distance = static_cast<ScreenGame*>(DecentEngine::Base::getScreen(0))->treeDistance();
	ScreenGame::fontRenderer.renderText(std::string("Tree Distance: ") + std::to_string(distance), glm::vec2(5.f), glm::vec2(1.f), glm::uvec4(0, 0, 0, 255));
	ScreenGame::fontRenderer.renderText("Press SPACE to fill the tree with presents!", glm::vec2(5.f, 768 - 37.f), glm::vec2(1.f), glm::uvec4(0, 255, 0, 255));
}
