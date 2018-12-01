#include "Asteroid.h"

int Asteroid::m_texId = 0;

Asteroid::Asteroid(const glm::vec2& position, const glm::vec2& size, float rotVelocity){
	//printf((std::string("assets/texture/asteroid-") + std::to_string((m_texId+1)) + std::string(".png")).c_str());
	object.init(position, size, glm::vec2(0), 0, rotVelocity, std::string("assets/textures/asteroid-") + std::to_string((m_texId+1)) + std::string(".png"));
	m_texId++;
	m_texId %= 5;
}

Asteroid::~Asteroid(){

}

void Asteroid::update(){

	if(object.getPosition().x > 1024.f + 20.f) object.setPosition(glm::vec2(-20.f, object.getPosition().y));
	if(object.getPosition().x < -20.f) object.setPosition(glm::vec2(1024 + 20.f, object.getPosition().y));
	if(object.getPosition().y > 1024.f + 20.f) object.setPosition(glm::vec2(object.getPosition().x, -20.f));
	if(object.getPosition().y < -20.f) object.setPosition(glm::vec2(object.getPosition().x, 1024 + 20.f));

	object.update();
}

void Asteroid::render(DecentEngine::SpriteBatch& batch){
	batch.addSprite(&object.sprite);
}
