#include "Player.h"

#include <SDL2/SDL.h>

#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>

Player::Player() {}
Player::~Player() {}

void Player::init(){
	object.init(glm::vec2(1024/ 2 + 25, 1024 / 2 + 25), glm::vec2(50), 0.f, "assets/textures/ship.png");
}

void Player::update(){
	if(DecentEngine::InputManager::isKeyDown(SDLK_w)){
		object.translateVelocity(glm::vec2(10.f) * DecentEngine::getHeading(object.getRotation() + 90.f));
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_d)){
		object.translateRotation(-180.f * DecentEngine::FPSRegulator::getDelta());
		//printf("Rotate\n");
	}
	if(DecentEngine::InputManager::isKeyDown(SDLK_a)){
		object.translateRotation(180.f * DecentEngine::FPSRegulator::getDelta());
	}

	if(object.getPosition().x > 1024.f + 20.f) object.setPosition(glm::vec2(-20.f, object.getPosition().y));
	if(object.getPosition().x < -20.f) object.setPosition(glm::vec2(1024 + 20.f, object.getPosition().y));
	if(object.getPosition().y > 1024.f + 20.f) object.setPosition(glm::vec2(object.getPosition().x, -20.f));
	if(object.getPosition().y < -20.f) object.setPosition(glm::vec2(object.getPosition().x, 1024 + 20.f));

	object.update();

	//printf("Velocity: %f, %f RotVelocity: %f\n", object.getVelocity().x, object.getVelocity().y, object.getRotationVelocity());
}
void Player::render(DecentEngine::SpriteBatch& batch){
	batch.addSprite(&object.sprite);	
}
