#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>

ScreenGame::ScreenGame() : m_player(false), m_ai(true){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f);	
	m_fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_player.init();
	m_ai.init();
	m_ball.init();
}
void ScreenGame::destroy() {
	m_fontRenderer.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());

	m_player.update(m_ball);
	m_ai.update(m_ball);
	m_ball.update();

	if(m_ball.object.getPosition().x > 1024.f) {
		m_plrPoints++;
		m_ball.object.setPosition(glm::vec2(1024/2, 768/2));	
	}
	if(m_ball.object.getPosition().x <= 0.f){
		m_aiPoints++;
		m_ball.object.setPosition(glm::vec2(1024/2, 768/2));
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_player.render();
	m_ai.render();
	m_ball.render();

	m_fontRenderer.setText(std::to_string(m_plrPoints), glm::vec2(30.f, 768.f - 42.f), glm::vec2(1.f), glm::uvec4(255));
	m_fontRenderer.render();

	m_fontRenderer.setText(std::to_string(m_aiPoints), glm::vec2(1024.f - 100.f, 768.f - 42.f), glm::vec2(1.f), glm::uvec4(255));
	m_fontRenderer.render();

	DecentEngine::RendererDefault::end();
}
