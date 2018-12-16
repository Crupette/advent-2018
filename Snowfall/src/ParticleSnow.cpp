#include "ParticleSnow.h"

ParticleSnow::ParticleSnow(float x, float size) : DecentEngine::Particle(glm::vec2(x, 800.f), glm::vec2(size), 0.f, glm::vec2(0.f, -200.f), 45.f, "blank", 0.f){
	
}

bool ParticleSnow::update(){
	object.update();

	if(object.getPosition().y < 10.f) return true;
	return false;
}
