#include "Elf.h"

#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/FPSRegulator.h>

Elf::Elf(glm::vec2 position){
	object.init(position, glm::vec2(90, 256), 0.f, "assets/textures/elf.png");
}

Elf::~Elf(){

}

bool Elf::update(){
	if(object.getPosition().y + object.aabb.getBounds().w <= 0.f){
		return false;
	}
	timeAlive += DecentEngine::FPSRegulator::getDelta();
	if(timeAlive >= 1.5f && !dead) click();
	if(dead) object.translateVelocity(glm::vec2(0.f, -10.f));
	object.update();
	return true;
}

void Elf::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Elf::click(){
	object.sprite.texture = DecentEngine::TextureCache::getTexture("assets/textures/elf-fell.png");
	object.translateVelocity(glm::vec2(0.f, 100.f));
	object.translateRotationVelocity(90.f);
	dead = true;
}
