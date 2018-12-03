#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f);	
	m_fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_player.init();

	m_remaining = 10;
}
void ScreenGame::destroy() {
	m_fontRenderer.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());

	if(m_loss) return;

	m_player.update();

	if(m_remaining > 0){
		std::uniform_int_distribution<int> chance(1, std::max(50 - (m_round * 5), 10));
		if(chance(m_engine) == 10){
			m_snow.emplace_back();
			m_remaining--;
		}
	}

	for(Snowflake& snowflake : m_snow){
		if(snowflake.update()){
			m_loss = true;
		}
	}

	for(size_t i = 0; i < m_bullets.size(); i++){
		if(!m_bullets[i].update()){
			m_bullets.erase(m_bullets.begin() + i);
			continue;
		}
		for(size_t j = 0; j < m_snow.size(); j++){
			if(DecentEngine::AABB::check(m_snow[j].object.aabb, m_bullets[i].object.aabb)){
				m_bullets.erase(m_bullets.begin() + i);
				m_snow.erase(m_snow.begin() + j);
				break;
			}
		}
	}
	
	if(m_timer > 0.f){
		m_timer -= DecentEngine::FPSRegulator::getDelta();
		if(m_timer <= 0.f){
			m_timer = 0.f;	
		}
	}

	if(m_timer == 0.f && m_snow.size() == 0 && m_remaining == 0){
		m_timer = 1.f;
		m_round++;
		m_remaining = 10 + m_round * 5;
	}

	if(DecentEngine::InputManager::isKeyPressed(SDLK_SPACE)){
		m_bullets.emplace_back(m_player.object.getPosition().x);
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_player.render();

	for(Bullet& bullet : m_bullets){
		bullet.render();
	}

	for(Snowflake& snowflake : m_snow){
		snowflake.render();
	}

	m_fontRenderer.setText(std::string("Round ") + std::to_string(m_round), glm::vec2(10, 10), glm::vec2(1), glm::uvec4(255));
	m_fontRenderer.render();

	if(m_loss){
		m_fontRenderer.setText("You Lose", glm::vec2(1024/2.f, 730.f), glm::vec2(1), glm::uvec4(255, 0, 0, 255));
		m_fontRenderer.render();
	}

	DecentEngine::RendererDefault::end();
}
