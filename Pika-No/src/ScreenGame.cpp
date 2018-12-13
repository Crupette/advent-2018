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

	glClearColor(0.5f, 0.5f, 1.f, 1.f);

	m_cat.init(glm::vec2(-600.f, 100.f), glm::vec2(236, 141) * glm::vec2(2.3), 0.f, "assets/textures/cat.png");
	m_background.init(glm::vec2(0), glm::vec2(1024, 768), 0.f, glm::uvec4(255), "assets/textures/background.png");
	m_steak.init(glm::vec2(700.f, 100.f), glm::vec2(300.f, 200.f), 0.f, glm::uvec4(255), "assets/textures/steak.png");
	m_timer = 0;

	m_audioManager.init();	
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
	m_audioManager.destroy();
}
void ScreenGame::update(){
	if(m_loss) return;
	bool prevRetreat = m_retreat;
	m_camera.update(DecentEngine::Base::getWindow());
	if(!m_going) m_timer += DecentEngine::FPSRegulator::getDelta();
	if(m_timer >= 1.f){
		m_timer = 0.f;
		m_going = true;
		std::uniform_real_distribution<float> speed(-50, 200);
		m_cat.translateVelocity(glm::vec2(800 + speed(m_engine), 0.f));
	}
	m_cat.update();
	if(m_cat.getPosition().x > 300){
		m_loss = true;
		m_audioManager.getSound("assets/sounds/lose.ogg").begin();
	}
	glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
	mousepos.y = 768 - mousepos.y;
	glm::vec4 bounds = m_cat.aabb.getBounds();
	if(mousepos.x > bounds.x && mousepos.x < bounds.x + bounds.z && mousepos.y > bounds.y && mousepos.y < bounds.y + bounds.w && DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		m_retreat = true;
		m_cat.translateVelocity(glm::vec2(-600.f, 0.f));
	}
	if(m_retreat && bounds.x <= -600.f){
		m_retreat = false;
		m_going = false;
		m_cat.setVelocity(glm::vec2(0.f));
	}
	if(prevRetreat == false && m_retreat){
		static DecentEngine::Audio::Sound sounds[13] {
			m_audioManager.getSound("assets/sounds/pika-1.ogg"),
			m_audioManager.getSound("assets/sounds/pika-2.ogg"),
			m_audioManager.getSound("assets/sounds/pika-3.ogg"),
			m_audioManager.getSound("assets/sounds/pika-4.ogg"),
			m_audioManager.getSound("assets/sounds/pika-5.ogg"),
			m_audioManager.getSound("assets/sounds/pika-6.ogg"),
			m_audioManager.getSound("assets/sounds/pika-7.ogg"),
			m_audioManager.getSound("assets/sounds/pika-8.ogg"),
			m_audioManager.getSound("assets/sounds/pika-9.ogg"),
			m_audioManager.getSound("assets/sounds/pika-10.ogg"),
			m_audioManager.getSound("assets/sounds/pika-11.ogg"),
			m_audioManager.getSound("assets/sounds/pika-12.ogg"),
			m_audioManager.getSound("assets/sounds/pika-13.ogg")
		};
		static int index = 0;
		sounds[index++].begin();
		index %= 13;
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	DecentEngine::RendererDefault::addSprite(&m_background);

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::begin(m_camera);

	DecentEngine::RendererDefault::addObject(&m_cat);
	DecentEngine::RendererDefault::addSprite(&m_steak);

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	DecentEngine::RendererDefault::endShader();
}
