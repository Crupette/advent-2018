#include "Child.h"

#include <Engine/RendererDefault.h>

Child::Child(glm::vec2 position){
	object.init(position, glm::vec2(32.f), 0.f, "assets/textures/circle.png");
	object.sprite.color = glm::uvec4(0, 0, 255, 255);
}

Child::~Child(){

}

void Child::update(glm::vec2 nearestPlayer, glm::vec2 nearestTree, bool treeFull){
	if(treeFull){
		if(nearestTree.x - object.getPosition().x > 0) {
			object.translateVelocity(glm::vec2(50.f, 0.f));
		}else{
			object.translateVelocity(glm::vec2(-50.f, 0.f));
		}
		if(nearestTree.y - object.getPosition().y > 0) {
			object.translateVelocity(glm::vec2(0.f, 50.f));
		}else{
			object.translateVelocity(glm::vec2(0.f, -50.f));
		}
	}else{
		if(nearestPlayer.x - object.getPosition().x > 0) {
			object.translateVelocity(glm::vec2(150.f, 0.f));
		}else{
			object.translateVelocity(glm::vec2(-150.f, 0.f));
		}
		if(nearestPlayer.y - object.getPosition().y > 0) {
			object.translateVelocity(glm::vec2(0.f, 150.f));
		}else{
			object.translateVelocity(glm::vec2(0.f, -150.f));
		}
	}
	object.update(10.f, 10.f);
}

void Child::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
