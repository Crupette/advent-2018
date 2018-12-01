#include "Bullet.h"

#include <Engine/FPSRegulator.h>

Bullet::Bullet(const glm::vec2& position, float rotation) : m_life(1.f){
	object.init(position, glm::vec2(15), glm::vec2(1024.f) * DecentEngine::getHeading(rotation), 0.f, 0.f, "assets/textures/circle.png");
}

bool Bullet::update() {
	m_life -= DecentEngine::FPSRegulator::getDelta();
	
	object.update();
	if(m_life < 0.f) return false;
	return true;
}

void Bullet::render(DecentEngine::SpriteBatch& batch){
	batch.addSprite(&object.sprite);
}
