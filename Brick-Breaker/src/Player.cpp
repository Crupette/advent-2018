#include "Player.h"

#include <Engine/RendererDefault.h>
#include <Engine/InputManager.h>

Player::Player(){

}

Player::~Player(){

}

void Player::init(){
	object.init(glm::vec2(1024 / 2.f, 5), glm::vec2(150, 20), 0.f, "blank");
}

void Player::update(){
	if(DecentEngine::InputManager::isKeyDown(SDLK_d)){
		object.translateVelocity(glm::vec2(512.f, 0.f));
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_a)){
		object.translateVelocity(glm::vec2(-512.f, 0.f));
	}

	object.update(5.f);

	glm::vec4 bounds = object.aabb.getBounds();
	if(bounds.x + bounds.z > 1024){
		object.setPosition(glm::vec2(1024 - bounds.z, 5));
	}
	if(bounds.x < 0){
		object.setPosition(glm::vec2(0, 5));
	}
}

void Player::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
