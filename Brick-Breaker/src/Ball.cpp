#include "Ball.h"

#include <ctime>

#include <Engine/RendererDefault.h>

std::mt19937 Ball::m_engine(time(0));

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity, bool diverge){
	object.init(position, glm::vec2(15, 15), velocity, 0.f, 0.f, "blank");
	if(diverge){
		std::uniform_real_distribution<float> divergence(-40.f, 40.f);
		object.translateVelocity(glm::vec2(divergence(m_engine), 0.f));
	}
}
Ball::~Ball(){

}

void Ball::update(){
	object.update();

	glm::vec4 bounds = object.aabb.getBounds();
	if(bounds.x < 0 || bounds.x + bounds.z > 1024) bounce(true, false);
	if(bounds.y + bounds.w > 768) bounce(false, true);
}

void Ball::render(){
	DecentEngine::RendererDefault::addObject(&object);
}

void Ball::bounce(bool dirx, bool diry){
	std::uniform_real_distribution<float> change(-45.f, 45.f);
	if(dirx){
		object.setVelocity(glm::vec2(-object.getVelocity().x, object.getVelocity().y));
	}
	if(diry){
		object.setVelocity(glm::vec2(object.getVelocity().x + change(m_engine), -object.getVelocity().y));
	}
}
