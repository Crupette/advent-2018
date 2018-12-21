#include "Piece.h"
#include "ScreenGame.h"

#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>

Piece::Piece(glm::uvec2 position, char character) : character(character), tilePosition(position), m_oldPosition(position) {
	object.init(glm::vec2(position) * glm::vec2(102.4f), glm::vec2(102.4f), 0.f, "assets/textures/piece.png");
}

Piece::~Piece(){

}

void Piece::update(){
	if(animating){
		m_progress += DecentEngine::FPSRegulator::getDelta();
		if(m_progress >= 0.2f) m_progress = 0.2f;
		float time = m_progress * (1 / 0.2f);
		if(time == 1.f){
			animating = false;
			object.setPosition(glm::vec2(tilePosition) * glm::vec2(102.4f));
		}else{
			glm::vec2 old = (glm::vec2(m_oldPosition) * glm::vec2(102.4f));
			glm::vec2 distance = (glm::vec2(tilePosition) * glm::vec2(102.4f)) - (glm::vec2(m_oldPosition) * glm::vec2(102.4f));
			object.setPosition(old + (distance * glm::vec2(m_progress)));
		}
	}else{
		m_progress = 0.f;
	}
	object.update();
}

void Piece::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Piece::renderText(){
	ScreenGame::fontRenderer.renderText(std::string(1, character), object.getPosition() + glm::vec2(24.f, 8.f), glm::vec2(2.f), glm::uvec4(0, 0, 0, 255));
}

void Piece::moveTo(glm::uvec2 newPosition){
	m_oldPosition = tilePosition;
	tilePosition = newPosition;
	animating = true;
}
