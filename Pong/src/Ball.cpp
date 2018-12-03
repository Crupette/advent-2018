#include "Ball.h"

#include <Engine/RendererDefault.h>

Ball::Ball() : m_engine(time(0)){

}

Ball::~Ball(){

}

void Ball::init(){
	object.init(glm::vec2(1024/2, 768/2), glm::vec2(10), 0.f, "assets/textures/ball.png");
	object.setVelocity(glm::vec2(800.f, 600.f/2.f));
}

void Ball::update(){
	if(object.getPosition().y <= 0 || object.getPosition().y > 768-20){
		object.setVelocity(glm::vec2(object.getVelocity().x, -object.getVelocity().y));
	}
	object.update();
}

void Ball::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Ball::bounce(){
	glm::vec2 velocity = object.getVelocity();
	std::uniform_real_distribution<float> random(-10.f, 10.f);
	object.setVelocity(glm::vec2(-velocity.x, velocity.y + random(m_engine)));
}
