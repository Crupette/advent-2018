#include "Brick.h"

#include <Engine/RendererDefault.h>

Brick::Brick(glm::vec2 position){
	object.init(position, glm::vec2(32.f), 0.f, "assets/textures/brick.png");
}

Brick::~Brick(){

}

void Brick::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
