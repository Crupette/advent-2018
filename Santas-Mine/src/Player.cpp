#include "Player.h"
#include "World.h"

#include <Engine/RendererDefault.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>

#include <algorithm>

int Player::maxDepth = 1;
int Player::money = 0;

Player::Player(){

}
Player::~Player(){

}

void Player::init(){
	object.init(glm::vec2(0, 60), glm::vec2(45, 95), 0.f, "assets/textures/player.png");
}
void Player::update(){
	if(DecentEngine::InputManager::isKeyDown(SDLK_w)){
		object.translatePosition(glm::vec2(0.f, 800.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
	}

	if(DecentEngine::InputManager::isKeyDown(SDLK_s)){
		object.translatePosition(glm::vec2(0.f, -800.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
	}
	
	if(DecentEngine::InputManager::isKeyDown(SDLK_d)){
		object.translatePosition(glm::vec2(800.f, 0.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
	}

	if(DecentEngine::InputManager::isKeyDown(SDLK_a)){
		object.translatePosition(glm::vec2(-800.f, 0.f) * glm::vec2(DecentEngine::FPSRegulator::getDelta()));
	}

	if(object.getPosition().y < maxDepth * 50 * -100){
		object.setPosition(glm::vec2(object.getPosition().x, maxDepth * 50 * -100));
	}

	object.update();

}
void Player::render(){
	
}
