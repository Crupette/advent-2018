#include "FireworkBase.h"

#include <Engine/FPSRegulator.h>
#include <Engine/ParticleEngine.h>

#include <ctime>

std::mt19937 FireworkBase::m_engine(time(0));

FireworkBase::FireworkBase(glm::vec2 position, float life) : DecentEngine::Particle(position,  glm::vec2(10), 0.f, glm::vec2(0.f, 200.f), 0.f, "blank", life) {
	object.sprite.color = glm::uvec4(255, 128, 0, 255);
} 

FireworkBase::~FireworkBase(){

}

FireworkSpark::FireworkSpark(glm::vec2 position, glm::vec2 velocity, int color, float life) : DecentEngine::Particle(position, glm::vec2(10), 0.f, velocity, velocity.x, "blank", life) {
	static glm::uvec4 colors[5] = {
		glm::uvec4(255, 0, 0, 255),
		glm::uvec4(255, 128, 0, 255),
		glm::uvec4(255, 255, 0, 255),
		glm::uvec4(0, 0, 255, 255),
		glm::uvec4(255)
	};
	object.sprite.color = colors[color];
}

FireworkSpark::~FireworkSpark(){

}

bool FireworkBase::update(){
	m_life -= DecentEngine::FPSRegulator::getDelta();
	if(m_life <= 0.f){
		std::uniform_real_distribution<float> life(0.4f, 0.8f);
		std::uniform_real_distribution<float> velocity(-400.f, 400.f);
		std::uniform_int_distribution<int> colorchn(0, 4);
		int color = colorchn(m_engine);
		for(size_t i = 0; i < 100; i++){
			DecentEngine::ParticleEngine::addParticle(new FireworkSpark(object.getPosition(), glm::vec2(velocity(m_engine), velocity(m_engine)), color, life(m_engine)));
		}
		return true;
	}
	object.update();
	return false;
}

bool FireworkSpark::update(){
	m_life -= DecentEngine::FPSRegulator::getDelta();
	if(m_life <= 0.f){
		return true;
	}
	object.update();
	return false;
}
