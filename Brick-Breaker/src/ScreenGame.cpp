#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame(){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024 / 2.f, 768 / 2.f), 1.f, 0.f);	
	fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_player.init();
	for(size_t y = 0; y < 10; y++){
		for(size_t x = 0; x < 20; x++){
			m_bricks.emplace_back(glm::vec2(x * 51.2f, 700.f - y * 20.f));
		}
	}

	m_balls.emplace_back(glm::vec2(1024 / 2.f, 200.f), glm::vec2(0.f, 512.f), false);
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());
	if(m_loss) return;
	
	if(m_score % 200 == 0 && m_score > 0){
		for(size_t y = 0; y < 10; y++){
			for(size_t x = 0; x < 20; x++){
				m_bricks.emplace_back(glm::vec2(x * 51.2f, 700.f - y * 20.f));
			}
		}
	}

	for(auto& ball : m_balls){
		ball.update();
		for(size_t i = 0; i < m_bricks.size(); i++){
			if(DecentEngine::AABB::check(ball.object.aabb, m_bricks[i].object.aabb)){
				m_bricks.erase(m_bricks.begin() + i);
				ball.bounce(false, true);
				m_score++;
				if(m_score % 10 == 0){
					m_balls.emplace_back(ball.object.getPosition(), ball.object.getVelocity(), true);				
				}
			}
		}
		if(DecentEngine::AABB::check(ball.object.aabb, m_player.object.aabb)){
			ball.bounce(false, true);
		}
	}
	for(size_t i = 0; i < m_balls.size(); i++){
		if(m_balls[i].object.aabb.getBounds().y < 0) m_balls.erase(m_balls.begin() + i);
	}

	if(m_balls.size() == 0){
		m_loss = true;
	}

	m_player.update();
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_player.render();

	for(auto& brick : m_bricks){
		brick.render();
	}
	
	for(auto& ball : m_balls) {
		ball.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	fontRenderer.renderText(std::string("Score: ") + std::to_string(m_score), glm::vec2(5, 763 - 32), glm::vec2(1), glm::uvec4(255));
	if(m_loss) fontRenderer.renderText("You Lose", glm::vec2(1000 / 2.f, 768 - 37), glm::vec2(1), glm::uvec4(255, 0, 0, 255));

	DecentEngine::RendererDefault::endShader();
}
