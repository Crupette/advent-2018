#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f); 
	fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_player.init();
	for(size_t y = 0; y < 20; y++)
	for(size_t x = 0; x < 32; x++){
		std::uniform_int_distribution<int> chance(1, 25);
		if(chance(m_engine) == 1){
			m_bricks.emplace_back(glm::vec2(x * 32, 768 - y * 32));
		}
	}
	for(size_t i = 0; i < 15; i++){
		m_reindeer.emplace_back(glm::vec2(128.f + i * 32, 768.f - 32.f));
	}
	glClearColor(0.5f, 0.6f, 0.9f);
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());
	if(m_loss) return;
	m_player.update();

	for(size_t i = 0; i < m_reindeer.size(); i++){
		m_reindeer[i].update();
		for(Brick& brick : m_bricks){
			if(DecentEngine::AABB::checkRect(brick.object.aabb, m_reindeer[i].object.aabb)){
				m_reindeer[i].bounce();
			}
		}
		if(m_reindeer[i].object.aabb.getBounds().y < 0){
			m_loss = true;
			return;
		}
	}
	for(size_t i = 0; i < m_presents.size(); i++){
		m_presents[i].update();
		if(m_presents[i].object.aabb.getBounds().y > 768){
			m_presents.erase(m_presents.begin() + i);
			continue;
		}
		for(size_t j = 0; j < m_reindeer.size(); j++){
			if(DecentEngine::AABB::checkRect(m_reindeer[j].object.aabb, m_presents[i].object.aabb)){
				m_bricks.emplace_back(m_reindeer[j].object.getPosition());
				m_reindeer.erase(m_reindeer.begin() + j);
				m_presents.erase(m_presents.begin() + i);
				m_score++;
				continue;
			}
		}
		for(size_t j = 0; j < m_bricks.size(); j++){
			if(DecentEngine::AABB::checkRect(m_bricks[j].object.aabb, m_presents[i].object.aabb)){
				m_bricks[j].health--;
				if(m_bricks[j].health == 0){
					m_bricks.erase(m_bricks.begin() + j);
				}
				m_presents.erase(m_presents.begin() + i);
				continue;
			}
		}
	}

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		m_presents.emplace_back(m_player.object.getPosition());
	}

	if(m_reindeer.empty()){
		for(size_t i = 0; i < 15; i++){
			m_reindeer.emplace_back(glm::vec2(128.f + i * 32, 768.f - 32.f));
		}
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_player.render();

	for(Brick& brick : m_bricks){
		brick.render();
	}
	for(Reindeer& reindeer : m_reindeer){
		reindeer.render();
	}
	for(Present& present : m_presents){
		present.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	fontRenderer.renderText(std::string("Score: ") + std::to_string(m_score), glm::vec2(5, 768 - 57), glm::vec2(1), glm::uvec4(255));
	if(m_loss) fontRenderer.renderText("YOU LOSE!", glm::vec2(500.f, 768 - 57), glm::vec2(1), glm::uvec4(255, 0, 0, 255));

	DecentEngine::RendererDefault::endShader();
}
