#include "Cat.h"

#include <string>

#include <Engine/RendererDefault.h>
#include <Engine/FPSRegulator.h>

Cat::Cat(glm::vec2 position, int skin){
	static std::string textures[2] = {
		"assets/textures/cat1.png",
		"assets/textures/cat2.png"
	};
	object.init(position, glm::vec2(128.f), 0.f, textures[skin]);
}

Cat::~Cat(){

}

bool Cat::update(){
	life -= DecentEngine::FPSRegulator::getDelta();
	if(life <= 0.f){
		return false;
	}	
	return true;
}

void Cat::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
