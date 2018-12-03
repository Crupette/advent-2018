#include "Player.h"

#include <Engine/RendererDefault.h>
#include <Engine/InputManager.h>

Player::Player(){

}

Player::~Player(){

}

void Player::init(){
	object.init(glm::vec2(1024.f/2.f, 15.f), glm::vec2(100.f, 40.f), 0.f, "assets/textures/player.png");
}

void Player::update(){
	if(DecentEngine::InputManager::isKeyDown(SDLK_d)){
		if(object.getPosition().x + 100.f < 1024.f) {
			object.translateVelocity(glm::vec2(400.f, 0.f));
		}
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_a)){
		if(object.getPosition().x > 0.f) {
			object.translateVelocity(glm::vec2(-400.f, 0.f));
		}
	}

	object.update(2.f);
}

void Player::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
