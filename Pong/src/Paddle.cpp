#include "Paddle.h"

#include <Engine/RendererDefault.h>
#include <Engine/FPSRegulator.h>
#include <Engine/InputManager.h>

std::mt19937 Paddle::m_engine(time(0));

Paddle::Paddle(bool side) : m_side(side) {

}

Paddle::~Paddle(){

}

void Paddle::init(){
	if(m_side){
		object.init(glm::vec2(1024.f - 20.f, 768.f / 2.f), glm::vec2(10.f, 200.f), 0.f, "blank");
	}else{
		object.init(glm::vec2(0.f, 768.f / 2.f), glm::vec2(10.f, 200.f), 0.f, "blank");
	}
}

void Paddle::update(Ball& ball){
	if(!m_side){
		if(DecentEngine::InputManager::isKeyDown(SDLK_w)){
			object.translatePosition(glm::vec2(0.f, 768.f/2.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
		}
		if(DecentEngine::InputManager::isKeyDown(SDLK_s)){
			object.translatePosition(glm::vec2(0.f, -768.f/2.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
		}
	}else{
		std::uniform_real_distribution<float> random(-110.f, 110.f);
		float ballY = ball.object.getPosition().y - 100.f + random(m_engine);
		if(object.getPosition().y > ballY){
			object.translatePosition(glm::vec2(0.f, -768.f/2.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
		}
		if(object.getPosition().y < ballY){
			object.translatePosition(glm::vec2(0.f, 768.f/2.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
		}
	}
	if(DecentEngine::AABB::check(object.aabb, ball.object.aabb)){
		ball.bounce();
	}
	object.update();
}

void Paddle::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
