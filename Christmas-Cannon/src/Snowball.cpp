#include "Snowball.h"

#include <Engine/RendererDefault.h>

Snowball::Snowball(){

}

Snowball::~Snowball(){

}

void Snowball::init(){
	object.init(glm::vec2(-100.f, 10.f), glm::vec2(75.f), 0.f, "assets/textures/ball.png");
}

void Snowball::update(){
	if(!landed){
		if(launched){
			object.translateVelocity(glm::vec2(0.f, -25.f));
			object.update(aerodynamics);
		}
	}
}

void Snowball::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Snowball::launch(glm::vec2 position, glm::vec2 heading){
	object.setPosition(position);
	object.translateVelocity(heading * glm::vec2(200 * power));
	launched = true;
	landed = false;
}
