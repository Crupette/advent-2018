#include "Player.h"

#include <Engine/RendererDefault.h>
#include <Engine/InputManager.h>

void Player::init(){
	object.init(glm::vec2(0.f), glm::vec2(32.f), 0.f, "assets/textures/circle.png");
	object.sprite.color = glm::uvec4(255, 0, 0, 255);
}

void Player::update(){
	if(DecentEngine::InputManager::isKeyDown(SDLK_w)){
		object.translateVelocity(glm::vec2(0.f, 250.f));	
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_s)){
		object.translateVelocity(glm::vec2(0.f, -250.f));	
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_a)){
		object.translateVelocity(glm::vec2(-250.f, 0.f));	
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_d)){
		object.translateVelocity(glm::vec2(250.f, 0.f));	
	}

	object.update(10.f, 10.f);
}

void Player::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
