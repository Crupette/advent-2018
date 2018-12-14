#include "ScreenGame.h"
#include "World.h"

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
	m_audioManager.init();

	glClearColor(0.5f, 0.5f, 1.f, 1.f);
	DecentEngine::Base::getWindow()->setIcon("assets/textures/ball.png");

	m_ball.init(glm::vec2(0.f, 768 / 2.f), glm::vec2(32.f), 0.f, "assets/textures/ball.png");
	m_ball.translateVelocity(glm::vec2(1024 / 2.f, 0.f));

	World::init();
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
	m_audioManager.destroy();
	World::destroy();
}
void ScreenGame::update(){
	m_camera.setPosition(glm::vec2(m_ball.getPosition().x, 768 / 2.f));
	m_camera.update(DecentEngine::Base::getWindow());

	m_ball.update();
	m_ball.translateVelocity(glm::vec2(0.f, -50.f));
	m_timer += DecentEngine::FPSRegulator::getDelta();
	for(DecentEngine::Object& object : World::terrain){
		if(DecentEngine::AABB::check(object.aabb, m_ball.aabb)){
			m_ball.setVelocity(glm::vec2(1024 / 2.f, 1000.f));
			if(m_timer > 0.25f){
				static DecentEngine::Audio::Sound sounds[8] = {
					m_audioManager.getSound("assets/sounds/bounce1.ogg"),
					m_audioManager.getSound("assets/sounds/bounce2.ogg"),
					m_audioManager.getSound("assets/sounds/bounce3.ogg"),
					m_audioManager.getSound("assets/sounds/bounce4.ogg"),
					m_audioManager.getSound("assets/sounds/bounce5.ogg"),
					m_audioManager.getSound("assets/sounds/bounce6.ogg"),
					m_audioManager.getSound("assets/sounds/bounce7.ogg"),
					m_audioManager.getSound("assets/sounds/bounce8.ogg")
				};
				std::uniform_int_distribution<int> tone(0, 7);
				sounds[tone(m_engine)].begin();
				m_timer = 0.f;
			}
		}
	}

	World::update(m_ball.getPosition());
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	World::render();
	DecentEngine::RendererDefault::addObject(&m_ball);

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	DecentEngine::RendererDefault::endShader();
}
