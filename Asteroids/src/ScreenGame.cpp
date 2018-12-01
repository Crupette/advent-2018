#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_shader = new DecentEngine::ShaderHandler();

	m_shader->addShader(GL_VERTEX_SHADER, "assets/shaders/base.vert");
	m_shader->addShader(GL_FRAGMENT_SHADER, "assets/shaders/base.frag");

	m_shader->buildProgram();

	m_shader->addAttribute("position");
	m_shader->addAttribute("color");
	m_shader->addAttribute("uv");

	m_batch.init();

	m_camera.init(glm::vec2(1024 / 2, 768 / 2), 1.f, 0.f);	

	m_player.init();

	m_asteroids.emplace_back(glm::vec2(100, 100), glm::vec2(100), 0.f);

	m_fontRenderer.init("assets/fonts/Vera.ttf", 32);
}
void ScreenGame::destroy() {
	m_fontRenderer.destroy();
	m_batch.destroy();

	delete m_shader;
}
void ScreenGame::update(){
	if(m_lives <= 0) return;
	m_immortalTime -= DecentEngine::FPSRegulator::getDelta();
	
	m_camera.update(DecentEngine::Base::getWindow());
	m_player.update();

	if(DecentEngine::InputManager::isKeyPressed(SDLK_SPACE)){
		m_bullets.emplace_back(m_player.object.getPosition() + (m_player.object.getSize() / glm::vec2(2.f)), m_player.object.getRotation() + 90.f);
	}

	for(size_t i = 0; i < m_asteroids.size(); i++) {
		m_asteroids[i].update();
		if(DecentEngine::AABB::check(m_asteroids[i].object.aabb, m_player.object.aabb) && m_immortalTime < 0.f){
			destroyAsteroid(i);
			m_lives--;
			m_immortalTime = 1.f;
			continue;
		}
	}
	for(size_t i = 0; i < m_bullets.size(); i++){
		if(!m_bullets[i].update()){
			m_bullets.erase(m_bullets.begin() + i);
			continue;
		}
		for(size_t j = 0; j < m_asteroids.size(); j++){
			if(DecentEngine::AABB::check(m_bullets[i].object.aabb, m_asteroids[j].object.aabb)){
				destroyAsteroid(j);
				m_bullets.erase(m_bullets.begin() + i);
				m_score++;
				break;
			}
		}
	}
}
void ScreenGame::render(){
	m_shader->use();

	m_camera.loadUniform(m_shader);
	glActiveTexture(GL_TEXTURE0);

	m_batch.begin();

	m_player.render(m_batch);

	for(Asteroid& asteroid : m_asteroids){
		asteroid.render(m_batch);
	}
	for(Bullet& bullet : m_bullets){
		bullet.render(m_batch);
	}

	m_batch.end();
	m_batch.renderBatches();

	m_fontRenderer.setText(std::string("Score:") + std::to_string(m_score), glm::vec2(5, 768 - 37), glm::vec2(1), glm::vec4(255));
	m_fontRenderer.render();
	m_fontRenderer.setText(std::string("Lives:") + std::to_string(m_lives), glm::vec2(5, 768 - 74), glm::vec2(1), glm::vec4(255));
	m_fontRenderer.render();
	m_fontRenderer.setText("YOU LOOSE", glm::vec2(500, 768 - 37), glm::vec2(1), glm::vec4(255, 0, 0, 255));
	if(m_lives <= 0){
		m_fontRenderer.render();
	}

	m_shader->unuse();
}

void ScreenGame::destroyAsteroid(size_t j){
	if(m_asteroids[j].object.getSize().x / 2.f > 25.f){
		for(size_t i = 0; i < 4; i++){
			std::uniform_real_distribution<float> velr(-50.f, 50.f);
			m_asteroids.emplace_back(m_asteroids[j].object.getPosition(), m_asteroids[j].object.getSize() / glm::vec2(1.2f), m_asteroids[j].object.getRotationVelocity() + velr(m_engine));
			m_asteroids.back().object.translateVelocity(m_asteroids[j].object.getVelocity() + glm::vec2(velr(m_engine), velr(m_engine)));
		}
	}
	m_asteroids.erase(m_asteroids.begin() + j);
}
