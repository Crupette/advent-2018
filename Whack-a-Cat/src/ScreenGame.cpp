#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f);
	DecentEngine::ParticleEngine::useCamera(&m_camera);
	fontRenderer.init("assets/fonts/Vera.ttf", 32);
	m_audioManager.init();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	DecentEngine::Base::getWindow()->setIcon("assets/textures/cat1.png");

	m_background.init(glm::vec2(0), glm::vec2(1024, 768), 0.f, glm::uvec4(255), "assets/textures/background.png");
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
	m_audioManager.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());
	m_timer -= DecentEngine::FPSRegulator::getDelta();
	if(m_timer <= 0.f){
		std::uniform_real_distribution<float> reset(0.5f, 1.f);
		m_timer = reset(m_engine);
		std::uniform_real_distribution<float> positionX(100.f, 800.f);
		std::uniform_real_distribution<float> positionY(64.f, 768.f - 64.f);
		std::uniform_int_distribution<int> skin(0, 1);
		m_cats.emplace_back(glm::vec2(positionX(m_engine), positionY(m_engine)), skin(m_engine));
	}
	for(size_t i = 0; i < m_cats.size(); i++){
		if(m_cats[i].update() == false){
			m_cats.erase(m_cats.begin(), m_cats.begin() + i);
		}
		if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
			glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
			mousepos.y = 768 - mousepos.y;
			glm::vec4 catbounds = m_cats[i].object.aabb.getBounds();
			if(mousepos.x > catbounds.x && mousepos.x < catbounds.x + catbounds.z && mousepos.y > catbounds.y && mousepos.y < catbounds.y + catbounds.w){
				m_score++;
				m_cats[i].object.setPosition(glm::vec2(-1000.f));
				m_cats[i].object.update();
				static DecentEngine::Audio::Sound sounds[5] {
					m_audioManager.getSound("assets/sounds/Cats.ogg"),
					m_audioManager.getSound("assets/sounds/Cats-2.ogg"),
					m_audioManager.getSound("assets/sounds/Cats-3.ogg"),
					m_audioManager.getSound("assets/sounds/Cats-4.ogg"),
					m_audioManager.getSound("assets/sounds/Cats-5.ogg")
				};
				std::uniform_int_distribution<int> current(0, 4);
				sounds[current(m_engine)].begin();
			}
		}
	}
	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		m_clicks++;
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	DecentEngine::RendererDefault::addSprite(&m_background);

	for(Cat& cat : m_cats){
		cat.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	fontRenderer.renderText(std::string("Score: ") + std::to_string(m_score), glm::vec2(5.f, 768 - 37.f), glm::vec2(1.f), glm::uvec4(0, 255, 0, 255));
	fontRenderer.renderText(std::string("Clicks: ") + std::to_string(m_clicks), glm::vec2(5.f, 768 - 69.f), glm::vec2(1.f), glm::uvec4(255, 0, 0, 255));

	DecentEngine::RendererDefault::endShader();
}
