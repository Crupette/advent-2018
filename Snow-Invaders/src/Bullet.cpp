#include "Bullet.h"

#include <Engine/RendererDefault.h>

Bullet::Bullet(float x){
	object.init(glm::vec2(x + 47.5f, 20.f), glm::vec2(5.f, 10.f), 0.f, "blank");
	object.setVelocity(glm::vec2(0.f, 768.f));
}

Bullet::~Bullet(){

}

bool Bullet::update(){
	if(object.getPosition().y >= 768.f){
		return false;
	}
	object.update();
	return true;
}

void Bullet::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
