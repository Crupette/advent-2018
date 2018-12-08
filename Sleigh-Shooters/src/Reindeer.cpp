#include "Reindeer.h"

#include <Engine/RendererDefault.h>

Reindeer::Reindeer(glm::vec2 position){
	object.init(position, glm::vec2(32.f), glm::vec2(-256.f, 0.f), 0.f, 0.f, "assets/textures/reindeer.png");
}

Reindeer::~Reindeer(){

}

void Reindeer::update(){
	object.update();
	glm::vec4 bounds = object.aabb.getBounds();
	if(bounds.x < 0 || bounds.x + bounds.z > 1024){
		object.translatePosition(glm::vec2(0, -32));
		object.setVelocity(glm::vec2(-object.getVelocity().x, 0.f));
		if(bounds.x < 0) object.setPosition(glm::vec2(0, object.getPosition().y));
		if(bounds.x + bounds.z > 1024) object.setPosition(glm::vec2(1024 - 32, object.getPosition().y));
	}
}

void Reindeer::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Reindeer::bounce(){
	object.translatePosition(glm::vec2(0, -32));
	object.setVelocity(glm::vec2(-object.getVelocity().x, 0.f));
}
